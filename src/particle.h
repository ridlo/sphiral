#ifndef PARTICLE_H
#define PARTICLE_H

struct particle{
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    double ax;
    double ay;
    double az;
    double m; // mass
    double r; // radius
    double h; // smoothing length
    double c; // speed of sound
    double rho; // density
    double P; // pressure
    double E; // internal energy
};

extern struct particle* particles;
extern int N;
extern int Nmax;
extern int N_active;

void particle_add(struct particle pt);

void print_particle_pos();
void print_particle_vel();
void print_particle_acc();

#endif
