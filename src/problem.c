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
    struct particle p1, p2;
    p1.x = tools_uniform(2., 3.);
    p1.y = tools_uniform(2., 3.);
    p1.z = tools_uniform(2., 3.);
    particle_add(p1);
    
    p2.x = tools_normal(0.5);
    p2.y = tools_normal(0.5);
    p2.z = tools_normal(0.5);
    particle_add(p2);

}

void problem_output(){
    output_particle_pos();
}

void problem_inloop(){
}

void problem_finish(){
}
    
