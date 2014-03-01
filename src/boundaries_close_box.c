#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "integrator.h"
#include "problem.h"
#include "kernel.h"
#include "boundaries.h"

int nghostx = 0;
int nghosty = 0;
int nghostz = 0;

// number of ghost particle 
int ghost_particle = 0;

// do nothing
void boundaries_collision(struct particle pt, int id_boundaries){
}

void boundaries_clean(){
    // remove ghost particle
}

void boundaries_check(){
    int i;
    int N_particles = N; // save before adding ghost particle
    for (i=0; i<N_particles; i++){
        if (particles[i].x < 2.*h){
            struct particle pt;
            pt.x  = -particles[i].x;
            pt.y  = particles[i].y;
            pt.z  = particles[i].z;
            pt.vx = -particles[i].vx;
            pt.vy = particles[i].vy;
            pt.vz = particles[i].vz;
            pt.ax = 0.;
            pt.ay = 0.;
            pt.az = 0.;
            pt.m = particles[i].m;
            pt.r = particles[i].r;
            particle_add(pt); 
       /* add ghost particle in the same array of real particles */
        }
        if (particles[i].x > (boxsize_x - 2.*h)){
            struct particle pt;
            pt.x  = (2.*boxsize_x - particles[i].x);
            pt.y  = particles[i].y;
            pt.z  = particles[i].z;
            pt.vx = -particles[i].vx;
            pt.vy = particles[i].vy;
            pt.vz = particles[i].vz;
            particle_add(pt);
            pt.ax = 0.;
            pt.ay = 0.;
            pt.az = 0.;
            pt.m = particles[i].m;
            pt.r = particles[i].r;
        }
        if (particles[i].y < 2.*h){
            struct particle pt;
            pt.x  = particles[i].x;
            pt.y  = -particles[i].y;
            pt.z  = particles[i].z;
            pt.vx = particles[i].vx;
            pt.vy = -particles[i].vy;
            pt.vz = particles[i].vz;
            pt.ax = 0.;
            pt.ay = 0.;
            pt.az = 0.;
            pt.m = particles[i].m;
            pt.r = particles[i].r;
            particle_add(pt);
        }
        if (particles[i].y > (boxsize_y - 2.*h)){
            struct particle pt;
            pt.x  = particles[i].x;
            pt.y  = (2.*boxsize_y - particles[i].y);
            pt.z  = particles[i].z;
            pt.vx = particles[i].vx;
            pt.vy = -particles[i].vy;
            pt.vz = particles[i].vz;
            pt.ax = 0.;
            pt.ay = 0.;
            pt.az = 0.;
            pt.m = particles[i].m;
            pt.r = particles[i].r;
            particle_add(pt);
        }
        if (particles[i].z < 2.*h){
            struct particle pt;
            pt.x  = particles[i].x;
            pt.y  = particles[i].y;
            pt.z  = -particles[i].z;
            pt.vx = particles[i].vx;
            pt.vy = particles[i].vy;
            pt.vz = -particles[i].vz;
            pt.ax = 0.;
            pt.ay = 0.;
            pt.az = 0.;
            pt.m = particles[i].m;
            pt.r = particles[i].r;
            particle_add(pt);
        }
        if (particles[i].z < 2.*h){
            struct particle pt;
            pt.x  = particles[i].x;
            pt.y  = particles[i].y;
            pt.z  = (2*boxsize_y - particles[i].z);
            pt.vx = particles[i].vx;
            pt.vy = particles[i].vy;
            pt.vz = -particles[i].vz;
            pt.ax = 0.;
            pt.ay = 0.;
            pt.az = 0.;
            pt.m = particles[i].m;
            pt.r = particles[i].r;
            particle_add(pt);
        }
        ghost_particle += 1;
    }
}

struct ghostbox boundaries_get_ghostbox(int i, int j, int k){
    struct ghostbox gb;
    gb.shiftx = boxsize_x*(double)i;
    gb.shifty = boxsize_y*(double)j;
    gb.shiftz = boxsize_z*(double)k;
    gb.shiftvx = 0;
    gb.shiftvy = 0;
    gb.shiftvz = 0;
    return gb;
}

