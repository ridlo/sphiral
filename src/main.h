#ifndef MAIN_H
#define MAIN_H

#ifndef M_PI
// make sure M_PI is defined
#define M_PI 3.14159265358979323846
#endif

extern double t;
extern double dt;
extern double tmax;
extern int exit_simulation;
extern double timing_initial;

extern int root_nx;
extern int root_ny;
extern int root_nz;
extern int root_n;
extern double boxsize;
extern double boxsize_x;
extern double boxsize_y;
extern double boxsize_z;
extern double boxsize_max;

/*
Initialize the box.
This function needs to be called from problem_init() before any particles are added
*/
void init_box();
void init_boxwidth(double _boxwidth);

// Main iteration loop.
void iterate();

#endif


