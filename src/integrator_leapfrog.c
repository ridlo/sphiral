/*
*
* Integrator: Leapfrog - DKD Scheme
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"

// DRIFT
void integrator_part1(){
    int i=0;
    for (i=0; i<N; i++){
        particles[i].x += 0.5*dt*particles[i].vx;
        particles[i].y += 0.5*dt*particles[i].vy;
        particles[i].z += 0.5*dt*particles[i].vz;
    }
    t += dt/2.;
}

// KICK & DRIFT
void integrator_part2(){
    int i=0;
    for (i=0; i<N; i++){
        particles[i].vx += dt*particles[i].ax;
        particles[i].vy += dt*particles[i].ay;
        particles[i].vz += dt*particles[i].az;
        particles[i].x += 0.5*dt*particles[i].vx;
        particles[i].y += 0.5*dt*particles[i].vy;
        particles[i].z += 0.5*dt*particles[i].vz;
    }
    t += dt/2.;
}

