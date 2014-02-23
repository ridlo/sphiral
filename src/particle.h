#ifndef PARTICLE_H
#define PARTICLE_H

struct particle{
    float x;
    float y;
    float z;
    float vx;
    float vy;
    float vz;
    float ax;
    float ay;
    float az;
    float m; // mass
    float r; // radius
    float h; // smoothing length
    float rho; // density
    float P; // pressure
};

extern struct particle* particles;

void particle_add(struct particle pt);

void print_particle_pos();
void print_particle_vel();
void print_particle_acc();

#endif
