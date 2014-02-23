#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "integrator.h"
#include "boundaries.h"

int nghostx = 0;
int nghosty = 0;
int nghostz = 0;

// do nothing
void boundaries_collision(){
}

// remove outsider particle
void boundaries_check(){
    int i;
    for (i=0; i<N; i++){
        int removep = 0;
        if (particles[i].x > boxsize_x/2.){
            removep = 1;
        }
        if (particles[i].x < -boxsize_x/2.){
            removep = 1;
        }
        if (particles[i].y > boxsize_y/2.){
            removep = 1;
        }
        if (particles[i].y < -boxsize_y/2.){
            removep = 1;
        }
        if (particles[i].z > boxsize_z/2.){
            removep = 1;
        }
        if (particles[i].z < -boxsize_z/2.){
            removep = 1;
        }
        if (removep == 1){
            printf("Remove particle %d. Outside boundaries.\n", i);
            if (N==1){
                printf("Last particle removed. Exiting. \n");
                exit(0);
            }

            particles[i] = particles[N-1]; // remove particle i and change with the last particle in array
            i--;
            N--;
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


// check if a given particle is within the comp domain
int boundaries_particle_is_in_box(struct particle p){
    if (p.x > boxsize_x/2.){
        return 0;
    }
    if (p.x < -boxsize_x/2.){
        return 0;
    }
    if (p.y > boxsize_y/2.){
        return 0;
    }
    if (p.y < -boxsize_y/2.){
        return 0;
    }
    if (p.z > boxsize_z/2.){
        return 0;
    }
    if (p.z < -boxsize_z/2.){
        return 0;
    }
    return 1;
}

