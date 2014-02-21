#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "particle.h"

struct particle* particles;
int N = 0;
int Nmax = 0;
int N_active = -1;

void particle_add(struct particle pt){
    Nmax += 128;
    particles = realloc(particles, sizeof(struct particle)*Nmax);
    particles[N] = pt;
    N++;
}

