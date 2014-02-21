/**
* MAIN
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/time.h>

#include "particle.h"
#include "output.h"
#include "tools.h"
#include "boundaries.h"

float t    = 0.;
float dt   = 0.;
float tmax = 0.;
float G    = 0.;
float softening        = 0.;
double timing_initial  = -1;
int exit_simulation    = 0;

static char* logo[];

float boxsize     = -1;
float boxsize_x   = -1;
float boxsize_y   = -1;
float boxsize_z   = -1;
float boxsize_max = -1;
int root_nx = 1;
int root_ny = 1;
int root_nz = 1;
int root_n  = 1;


void init_box(){
    if (boxsize <= 0){
        fprintf(stderr, "ERROR: Size of the boxsize has to be set and be positive.\n");
        exit(-1);
    }
    if (root_nx <= 0 || root_ny <= 0 || root_nz <= 0){
        fprintf(stderr, "ERROR: Number of root boxes must be greater or equal to 1 in each direction.\n");
        exit(-1);
    }

    // Remove all particles (empty start)
    free(particles);
    particles = NULL;

    // Setup box sizes
    boxsize_x = boxsize*(float)root_nx;
    boxsize_y = boxsize*(float)root_ny;
    boxsize_z = boxsize*(float)root_nz;
    root_n = root_nx*root_ny*root_nz;

    boxsize_max = boxsize_x;
    if (boxsize_max < boxsize_y) boxsize_max = boxsize_y;
    if (boxsize_max < boxsize_z) boxsize_max = boxsize_z;
    
    // print starting point
    printf("Initialized %d*%d*%d root boxes. Process id: %d\n", root_nx, root_ny, root_nz, getpid());
}

void init_boxwidth(float _boxwidth){
    boxsize = _boxwidth;
    init_box();
}


void iterate(){    
    // some iteration

    problem_output();

    struct timeval tim;
    gettimeofday(&tim, NULL);
    double timing_final = tim.tv_sec+(tim.tv_usec/1000000.0);
    printf("\nComputation finished. Total runtime: %f s\n", timing_final - timing_initial);

    exit(0);

}

int interrupt_counter = 0;
void interruptHandler(int var){
    // try to quit nicely
    switch(interrupt_counter){
        case 0:
            printf("\nInterrupt received. Will try to exit.\n");
            exit_simulation = 1;
            break;
        default:
            printf("\nInterrupt received. Will exit immediately.\n");
            exit(-1);
    }
    interrupt_counter++;
}




/* MAIN PROGRAM */
int main(int argc, char *argv[]){
    
    // display LOGO --- LOL    
    int i=0;
    while (logo[i] != NULL){ 
        printf("%s", logo[i++]);
    }

    // Store runtime 
    struct timeval tim;
    gettimeofday(&tim, NULL);
    timing_initial = tim.tv_sec+(tim.tv_usec/1000000.0);
    
    // initialiase  interrupts, random numbers, problem, etc
    signal(SIGINT, interruptHandler);
    signal(SIGKILL, interruptHandler);
    srand(tim.tv_usec + getpid());

    /* -------------------- */

    problem_init(argc, argv);
    iterate();

    return 0;
}


static char* logo[] = {
"               .__    .__              .__   \n",
"  ____________ |  |__ |__|___________  |  |  \n",
" /  ___/\\____ \\|  |  \\|  \\_  __ \\__  \\ |  |  \n",
" \\___ \\ |  |_> >   Y  \\  ||  | \\// __ \\|  |__\n",
"/____  >|   __/|___|  /__||__|  (____  /____/\n",
"     \\/ |__|        \\/               \\/      \n",
"     Copyright (c) 2014 Ridlo W. Wibowo      \n",
"         <ridlo.w.wibowo@gmail.com>          \n",
"       http://astrokode.wordpress.com        \n",
"                                             \n",
"                                             \n",
NULL};
