#ifndef FORCE_H
#define FORCE_H

struct vec3d{
    double x;
    double y;
    double z;
};

extern double kappa; // scalling factor for NNP
extern double eta; // dynamic h constant: 1.2-1.5 (Rosswog, 2009)

// viscosity term
extern double alpha_visc;
extern double beta_visc;
extern double epsi; // softening

extern int *pair_i;
extern int *pair_j;
extern int pair_max;

extern double *w;
extern struct vec3d *dw;


void force_calc_acceleration();

#endif
