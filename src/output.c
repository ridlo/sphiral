#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "particle.h"
#include "main.h"
#include "output.h"

void output_particle_pos(){
    int i;
    for (i=0; i<N; i++){
        printf("%f %f %f\n", particles[i].x, particles[i].y, particles[i].z);
    }
}

void output_particle_vel(){
    int i;
    for (i=0; i<N; i++){
        printf("%f %f %f\n", particles[i].vx, particles[i].vy, particles[i].vz);
    }
}

void output_particle_acc(){
    int i;
    for (i=0; i<N; i++){
        printf("%f %f %f\n", particles[i].ax, particles[i].ay, particles[i].az);
    }
}

void output_pos_asciifile(char* filename){
    int i;
    char fname[1024];
    sprintf(fname, "%s_%f.dat", filename, t);
    FILE* of = fopen(fname, "w");
    if (of == NULL){
        printf("\nError while opening file '%s'.\n", fname);
        return;
    }

    for (i=0; i<N; i++){
        fprintf(of, "%f %f %f\n", particles[i].x, particles[i].y, particles[i].z);
    }

    fclose(of);

}
