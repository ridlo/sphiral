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
    
    init_boxwidth(4);
    struct particle pt;
    
    FILE *ptr_file;
    char buf[1000];
    ptr_file = fopen("input_Planet.dat", "r");
    if (ptr_file==NULL){
        perror("Error while opening the file\n");
        exit(EXIT_FAILURE);
    }

    float m, x, y, z, vx, vy, vz;
    while (fgets(buf, 1000, ptr_file)!= NULL){
        sscanf(buf, "%f %f %f %f %f %f %f", &m, &x, &y, &z, &vx, &vy, &vz);
        pt.x = x;
        pt.y = y;
        pt.z = z;
        pt.vx = vx;
        pt.vy = vy;
        pt.vz = vz;
        pt.m = m;
        pt.r = 0.01;
        pt.h = 0.0;
        pt.rho = 1.1;
        pt.P = 0.0;
        particle_add(pt);
    }
    fclose(ptr_file);
}

void problem_output(){
    output_pos_asciifile("position");
}

void problem_inloop(){
}

void problem_finish(){
}
    
