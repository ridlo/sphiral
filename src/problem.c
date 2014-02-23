#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "particle.h"
#include "output.h"
#include "tools.h"
#include "boundaries.h"

void problem_init(int argc, char* argv[]){
    
    init_boxwidth(10);
    struct particle pt;
    N = 2500;

    int i, j, k;
    for (i=0; i<50; i++){

    particle_add(pt);
    

}

void problem_output(){
    output_particle_pos();
}

void problem_inloop(){
}

void problem_finish(){
}
    
