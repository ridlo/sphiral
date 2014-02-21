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

//void init_box();
//void iterate();

#endif


