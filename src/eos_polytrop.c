#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "main.h"
#include "problem.h"
#include "force.h"
#include "kernel.h"
#include "eos.h"

double K   = 0.015;
double gam = 2;

void eos_calculate_pressure(){
    for (int i=0; i<N; i++){
        particles[i].P = K*pow(particles[i].rho, gam);
    }
}

void eos_calculate_speedofsound(){
    for (int i=0; i<N; i++){
        particles[i].c = sqrt(gam*particles[i].P/particles[i].rho);
    }
}
