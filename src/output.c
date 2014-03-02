#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "particle.h"
#include "main.h"
#include "force.h"
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
    char fname[1024];
    sprintf(fname, "%s_%d.dat", filename, count_step);
    FILE* of = fopen(fname, "w");
    if (of == NULL){
        printf("\nError while opening file '%s'.\n", fname);
        return;
    }

    for (int i=0; i<N; i++){
        fprintf(of, "%f %f %f\n", particles[i].x, particles[i].y, particles[i].z);
    }

    fclose(of);

}


void output_pos_binary(char* filename){
    char fname[1024];
    sprintf(fname, "%s_%d.bin", filename, count_step);
    FILE* of = fopen(fname,"wb");
    if (of == NULL){
        printf("\nError while opening file '%s'. \n", fname);
        return;
    }

    for (int i=0; i<N; i++){
        struct vec3d v;
        v.x = particles[i].x;
        v.y = particles[i].y;
        v.z = particles[i].z;
        fwrite(&(v), sizeof(struct vec3d),1,of);
    }
    
    fclose(of);
}
