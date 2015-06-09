#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "parameters.h"
#include "msg.h"
#include "pm.h"

static double aa = 0;

static double mond_simple(double k2, Parameters * param) {
    double lambda1 = param->pm_mond_parameters[0];
    double s = param->pm_mond_parameters[1];

    double aas = pow(aa, s);
    double f1 = lambda1 * lambda1 * k2 * aas;
    double f2 = 1 + (4 / 3.) * f1;
    double f3 = 1 + f1;
    return f2 / f3;
}
pm_modulator MODULATOR = NULL;
void mond_init(Parameters * param) {
    switch(param->pm_mond_mode) {
        case PM_MOND_SIMPLE:
            MODULATOR = (pm_modulator) mond_simple; 
            break;
        default:
            msg_abort(9999, "mond mode unknown\n");
    }

}
pm_modulator mond_get_modulator() {
    return MODULATOR;
}

void mond_set_time(double time) {
    aa = time;
}