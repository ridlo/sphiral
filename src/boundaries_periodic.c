#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "integrator.h"
#include "boundaries.h"

int nghostx = 1;
int nghosty = 1;
int nghostz = 1;

// do nothing
void boundaries_collision(){
}

void boundaries_check(){
    int i;
    for (i=0; i<N; i++){
        while (particles[i].x > boxsize_x/2.){
            particles[i].x -= boxsize_x;
        }
        while (particles[i].x < -boxsize_x/2.){
            particles[i].x += boxsize_x;
        }
        while (particles[i].y > boxsize_y/2.){
            particles[i].y -= boxsize_y;
        }
        while (particles[i].y < -boxsize_y/2.){
            particles[i].y += boxsize_y;
        }
        while (particles[i].z > boxsize_z/2.){
            particles[i].z -= boxsize_z;
        }
        while (particles[i].z < -boxsize_z/2.){
            particles[i].z += boxsize_z;
        }
    }
}

struct ghostbox boundaries_get_ghostbox(int i, int j, int k){
    struct ghostbox gb;
    gb.shiftx = boxsize_x*(float)i;
    gb.shifty = boxsize_y*(float)j;
    gb.shiftz = boxsize_z*(float)k;
    gb.shiftvx = 0;
    gb.shiftvy = 0;
    gb.shiftvz = 0;
    return gb;
}

