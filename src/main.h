#ifndef MAIN_H
#define MAIN_H

#ifndef M_PI
// make sure M_PI is defined
#define M_PI 3.14159265358979323846
#endif

extern float t;
extern float dt;
extern float tmax;
extern float G;
extern int N;
extern int Nmax;
extern int N_active;
extern float softening;
extern int exit_simulation;
extern double timing_initial;

extern int root_nx;
extern int root_ny;
extern int root_nz;
extern int root_n;
extern float boxsize;
extern float boxsize_x;
extern float boxsize_y;
extern float boxsize_z;
extern float boxsize_max;

/*
Initialize the box.
This function needs to be called from problem_init() before any particles are added
*/
void init_box();
void init_boxwidth(float _boxwidth);

// Main iteration loop.
void iterate();

#endif


