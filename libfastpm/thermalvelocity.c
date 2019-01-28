#include <string.h>   //memcpy
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>

#include <fastpm/libfastpm.h>
#include <fastpm/store.h>    //isnt this in libfastpm?
//#include <fastpm/thermalvelocity.h>   //added to libfastpm?

#define LENGTH_FERMI_DIRAC_TABLE 4000 //sets the length of the table on which CDF
                                      //will be evaluated
#define MAX_FERMI_DIRAC          20.0 //Upper limit of F-D distribution in units of
                                      // p/T

#define NEXT(n, i)  (((n) + (i)/(n)) >> 1) // Needed for Healpix routine

//should i initialize all funcs here?????????????????????

//needed for healpix
unsigned int isqrt(int number) {
  unsigned int n  = 1;
  unsigned int n1 = NEXT(n, number);

  while(abs(n1 - n) > 1) {
    n  = n1;
    n1 = NEXT(n, number);
  }
  while(n1*n1 > number)
    n1--;
  return n1;
}


//Converts from pixel number to unit vector (needed for healpix)
void pix2vec (int pix, double *vec, int n_side)
{
  double z, phi;
  int nside_ = n_side;
  long ncap_=nside_*(nside_-1)*2;
  long npix_=12*nside_*nside_;
  double fact2_  = 4./npix_;
  if (pix<ncap_) /* North Polar cap */
    {
      int iring = (int)(0.5*(1+isqrt(1+2*pix))); /* counted from North pole */
      int iphi  = (pix+1) - 2*iring*(iring-1);

      z = 1.0 - (iring*iring)*fact2_;
      phi = (iphi-0.5) * 0.5*M_PI/iring;
    }
  else if (pix<(npix_-ncap_)) /* Equatorial region */
    {
      double fact1_  = (nside_<<1)*fact2_;
      int ip  = pix - ncap_;
      int iring = ip/(4*nside_) + nside_; /* counted from North pole */
      int iphi  = ip%(4*nside_) + 1;
      /* 1 if iring+nside is odd, 1/2 otherwise */
      double fodd = ((iring+nside_)&1) ? 1 : 0.5;

      int nl2 = 2*nside_;
      z = (nl2-iring)*fact1_;
      phi = (iphi-fodd) * M_PI/nl2;
    }
  else /* South Polar cap */
    {
      int ip = npix_ - pix;
      int iring = (int)(0.5*(1+isqrt(2*ip-1))); /* counted from South pole */
      int iphi  = 4*iring + 1 - (ip - 2*iring*(iring-1));

      z = -1.0 + (iring*iring)*fact2_;
      phi = (iphi-0.5) * 0.5*M_PI/iring;
    }

  vec[0] = sin(acos(z))*cos(phi);
  vec[1] = sin(acos(z))*sin(phi);
  vec[2] = z;
}


// Functional form of F-D distribution
double fermi_dirac_kernel(double x)
{
  return x * x / (exp(x) + 1);
}

// Samples the low velocity end more effectively
double low_vel_kernel(double x)
{
  return x / (exp(x) + 1);
}

// Needed for calculatin the velocity dispersion
double fermi_dirac_dispersion(double x)
{
  return x * x * x * x/ (exp(x) + 1);
}




void divide_fd(double *vel_table, double *mass, int n_shells)
{
  double fermi_dirac_vel_ncdm[LENGTH_FERMI_DIRAC_TABLE];
  double fermi_dirac_cdf_ncdm[LENGTH_FERMI_DIRAC_TABLE]; //stores CDF

  int i,j;
  double v_bin,u,bin_average,bin_mass;
  double vel_edges[n_shells];
  double result,error;
  gsl_integration_workspace * w
    = gsl_integration_workspace_alloc (1000);

  gsl_function F,G,H;
  F.function = &low_vel_kernel;
  G.function = &fermi_dirac_kernel;
  H.function = &fermi_dirac_dispersion;

  // Initialize the CDF table
  for(i = 0; i < LENGTH_FERMI_DIRAC_TABLE; i++){
    fermi_dirac_vel_ncdm[i] = MAX_FERMI_DIRAC * i / (LENGTH_FERMI_DIRAC_TABLE - 1.0);
    gsl_integration_qags (&F, 0, fermi_dirac_vel_ncdm[i], 0,1e-7 , 1000,
			  w, &result, &error);
    fermi_dirac_cdf_ncdm[i] = result;
  }

  //Normalize to 1
  for(i = 0; i < LENGTH_FERMI_DIRAC_TABLE; i++)
    fermi_dirac_cdf_ncdm[i] /= fermi_dirac_cdf_ncdm[LENGTH_FERMI_DIRAC_TABLE - 1];


  //Define the edges of the velocity bins (lower edge held to 0)
  for(i=0;i<n_shells;i++){
     v_bin = (i+1)/(n_shells*1.0);
     j=0;
     while(j < LENGTH_FERMI_DIRAC_TABLE - 2)
       if(v_bin > fermi_dirac_cdf_ncdm[j + 1])
	 j++;
       else
	 break;

     u = (v_bin - fermi_dirac_cdf_ncdm[j]) / (fermi_dirac_cdf_ncdm[j + 1] - fermi_dirac_cdf_ncdm[j]);

     vel_edges[i] = fermi_dirac_vel_ncdm[j] * (1 - u) + fermi_dirac_vel_ncdm[j + 1] * u;
  }

  //Get the bin velocities and bin masses
  double total_mass;
  gsl_integration_qags (&G, 0, fermi_dirac_vel_ncdm[LENGTH_FERMI_DIRAC_TABLE-1], 0,1e-7 , 1000,
			  w, &result, &error);
  total_mass = result;
  for(i=0;i<n_shells;i++){
    //Special case for lowest bin - left edge has to be zero
     if (i==0){
       gsl_integration_qags (&H, 0,vel_edges[i], 0,1e-7 , 1000,
			  w, &result, &error);
       bin_average = result;
       gsl_integration_qags (&G, 0, vel_edges[i], 0,1e-7 , 1000,
			  w, &result, &error);
       bin_average /= result;

       bin_mass = result/total_mass;
     }
     else{
       gsl_integration_qags (&H, vel_edges[i-1],vel_edges[i], 0,1e-7 , 1000,
			  w, &result, &error);
       bin_average = result;
       gsl_integration_qags (&G, vel_edges[i-1], vel_edges[i], 0,1e-7 , 1000,
			  w, &result, &error);
       bin_average /= result;

       bin_mass = result/total_mass;
     }
     vel_table[i] = sqrt(bin_average);
     mass[i] = bin_mass;
  }

}


void divide_sphere_healpix(double *vec_table, int n_side)  //so is the direction totally fixed? could we rotate the divisions relative to north pole (i.e. relative to the box)?
{
  int i,k;
  double v_sq[3];
  for(k=0;k<3;k++)
    v_sq[k] = 0.;
  // Get unit vectors for all pixels
  for(i=0;i<12*n_side*n_side;i++){
    pix2vec(i,&vec_table[i*3],n_side);
    for(k=0;k<3;k++)
      v_sq[k] += vec_table[i*3+k]*vec_table[i*3+k];
  }
  // Isotropize the velocity dispersion - important for low n_side    [should we remove this if for high n_side???]
  for(k=0;k<3;k++){
    v_sq[k] /= 12*n_side*n_side;
    v_sq[k] /= 1./3.; // Set each direction to have 1/3 of total dispersion
  }
  for(i=0;i<12*n_side*n_side;i++)
    for(k=0;k<3;k++)
      vec_table[i*3+k] /= sqrt(v_sq[k]);
}

void divide_sphere_fibonacci(double *vec_table, int n_fibonacci)
{
  double lat, lon;
  int i,j,k;
  int N_tot = 2*n_fibonacci+1;


  for (i=-n_fibonacci;i<n_fibonacci+1;i++){
    lat = asin(2.0*i/(2.0*n_fibonacci+1));
    lon = 2.0*M_PI*i*2.0/(1.0+sqrt(5.0));
    j = i + n_fibonacci;
    vec_table[j*3+0] = cos(lat)*cos(lon);
    vec_table[j*3+1] = cos(lat)*sin(lon);
    vec_table[j*3+2] = sin(lat);

  }

}


//all below is for healpix... can add fibonacci later.!!!!!!!!!!!!

static void _fastpm_ncdm_init_fill(FastPMncdmInitData* nid);

//create and fill the table
FastPMncdmInitData* 
fastpm_ncdm_init_create(double m_ncdm, double z, int n_shells, int n_side)
{
    FastPMncdmInitData* nid = malloc(sizeof(nid[0]));

    nid->m_ncdm = m_ncdm;
    nid->z = z;
    nid->n_shells = n_shells;
    nid->n_side = n_side;
    
    nid->n_split = 12 * n_shells * n_side*n_side;     //this is the total number of velocity vectors produced
    /* recall vel is a pointer to a 3 element array
    so lets make into multidim array of dim (n_split x 3) */
    nid->vel = calloc(nid->n_split, sizeof(double[3]));
    nid->mass = calloc(nid->n_split, sizeof(double));   //a 1d array to store all the masses.

    _fastpm_ncdm_init_fill(nid);
    
    return nid;
}

//free the table
void 
fastpm_ncdm_init_free(FastPMncdmInitData* nid)
{
    free(nid->vel);
    free(nid->mass);
    free(nid);
}

//append the table
static void
_fastpm_ncdm_init_fill(FastPMncdmInitData* nid)    ///call in create.  no need for it otherwise.
{   
    int n_shells = nid->n_shells;
    int n_side = nid->n_side;
    
    double *vel_table, *vec_table, *masstab;
    vel_table = malloc(sizeof(double)*n_shells);
    masstab = calloc(n_shells,sizeof(double));
    vec_table = malloc(sizeof(double)*12*n_side*n_side*3);
    
    divide_fd(vel_table,masstab,n_shells);

    divide_sphere_healpix(vec_table,n_side);

    double velocity_conversion_factor = 50.3*(1.+ nid->z)*(1./nid->m_ncdm); //In km/s in Gadget internal units
    //velocity_conversion_factor *= sqrt(1. + redshift); // Now in Gadget I/O units
    
    //DODGY FIX FOR OUR TEST RUN TO AVOID FLOATING POINT ERROR (I.E. make v the correct sort of order of mag):
    velocity_conversion_factor /= 1e6;

    int i, j, k;
    int r=0;                          //row num
    for(i=0;i<12*n_side*n_side;i++){
        for(j=0;j<n_shells;j++){
            nid->mass[r] = masstab[j]/(12.*n_side*n_side);              //THIS IS THE FRACTIONAL MASS! MULTIPLY BY M_NU
            for(k=0;k<3;k++){
                nid->vel[r][k] = vel_table[j]*vec_table[i*3+k]*velocity_conversion_factor;
            }
            r++;
        }
    }
    
    free(vel_table); 
    free(masstab);
    free(vec_table);
}


void
fastpm_split_ncdm(FastPMncdmInitData* nid, FastPMStore * src, FastPMStore * dest, int f_subsample)
{
    /*Takes store src, splits a fraction 1/f_subsample
    of src according to the ncdm init data, and uses this to
    populate an 'empty' (it's been init'd, but not lpt'd) store dest.
    For our test src is fully populated after calling the setup_lpt func
    */
    
    /*
    //create mask   [this isa long because we look through i twice, here and fastpm_store_subsample]
    uint8_t mask[p->np]; 
    ptrdiff_t i;
    for(i = 0; i < p->np; i ++) {
        mask[i] = !(i%f_subsample);
    }
    
    //subsample p
    FastPMStore * psub;
    
    fastpm_store_subsample(p, mask, psub);
    */
    
    //FIX COULD I COPY ith col over for each j, and thenjust change the id and velocity? DONE. maybe overkill copying all cols, but keeps thing general, rather than just assuming we only need to copy over x. 
    //maybe copy over the entire store, so that global info is copied, mass, anything else?? I think only the meta-data and columsn might need to be copied, everything else is dealt with when initilizing the ncdm store! Actually need np! What about np_upper? Should store_init not setthe np???? Maybe ask Yu, we should probably change this. Right now store_init sets np to 0 at the start, but if np_total is an arg, then why not set it to that? seems that init_evenly take np_total, but plain init  doesnt.
        //i think q_shift uneeded.
    //The problem with copying store is thatwe'd need to change the size which is a bit annoying.

    
    //copy meta-data. would dest->meta = src->meta; work or would that be a pointer? Based on store_subsample it would work.
    dest->meta.a_v = src->meta.a_v;
    dest->meta.a_x = src->meta.a_x;
    //dest->meta.M0 = src->meta.M0;
    //printf("\n%ld\n\n", dest->np);
    dest->np = src->np / f_subsample * nid->n_split;    //remove once store init does this?
    
    ptrdiff_t i;  //? apaz just a positive int used for indexing?
    int j, d;
    int k = 0;
    for(i = 0; i < src->np; i ++) {    //loop thru each cdm particle
        if( !(i%f_subsample) ){        //subsample. does i = src->id[i]? would be messy if not. would need to check memcpy too 
            for(j = 0; j < nid->n_split; j ++) {     //loop thru each each ncdm split velocity
                //copy all cols
                int c;
                for(c = 0; c < 32; c ++) {
                    if (!dest->columns[c]) continue;        //do we need this?

                    size_t elsize = dest->_column_info[c].elsize;
                    memcpy(dest->columns[c] + k * elsize, src->columns[c] + i * elsize, elsize);
                }
                
                //overwrite id and vel
                dest->id[k] = k;
                for(d = 0; d < 3; d ++){
                    //dest->x[k][d] = src->x[i][d];
                    dest->v[k][d] = nid->vel[j][d];
                }
                
                k ++;
            }
        }
    }
}

