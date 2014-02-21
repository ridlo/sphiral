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

float t = 0.;
float dt = 0.;
float tmax = 0.;
float G = 0.;
float softening = 0.;
double timing_initial = -1;
int exit_simulation = 0;
static char* logo[];



void iterate(){
    
    // some iteration

    problem_output();

    struct timeval tim;
    gettimeofday(&tim, NULL);
    double timing_final = tim.tv_sec+(tim.tv_usec/1000000.0);
    printf("\nComputation finished. Total runtime: %f s\n\n", timing_final - timing_initial);

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
            printf("Interrupt received. Will exit immediately.\n");
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
