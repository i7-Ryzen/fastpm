typedef enum {
    FASTPM_NCDM_SPHERE_HEALPIX = 0,
    FASTPM_NCDM_SPHERE_FIBONACCI = 1,
} FastPMncdmSphereScheme;

typedef struct FastPMncdmInitData{
    double BoxSize;
    double Omega_ncdm;
    double m_ncdm[3];
    int n_ncdm; /* number of ncdm species, each has a m_ncdm */
    double m_ncdm_sum; /* total ev mass of all ncdm */
    double z;   /* initialization redshift of ncdm species */

    int n_shells;
    int n_side;
    int lvk;    /* bool: switch on low velocity kernel? */

    FastPMncdmSphereScheme ncdm_sphere_scheme;
    
    size_t n_sphere; /* number of tiles on the sphere */
    size_t n_split; /* number of phase space splits of each initial position */
    /* a table for quick look up of the coherent thermal velocity and mass of split particles. */
    double (* vel)[3];
    double * mass;
} FastPMncdmInitData;

FastPMncdmInitData *
fastpm_ncdm_init_create(double BoxSize, double m_ncdm[3], int n_ncdm, double h, double z, int n_shells, int n_side, 
                        int lvk, FastPMncdmSphereScheme ncdm_sphere_scheme);

void
fastpm_ncdm_init_free(FastPMncdmInitData* nid);

void
fastpm_split_ncdm(FastPMncdmInitData* nid, FastPMStore * src, FastPMStore * dest, MPI_Comm comm);
