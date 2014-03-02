#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "boundaries.h"
#include "kernel.h"
#include "force.h"
#include "problem.h"
#include "gravityinteract.h"

double G = 1.0;
double gravity_constant = -1;

struct vec3d kernel_gravity_gradient(double dx, double dy, double dz, double r, double h){
    struct vec3d gravity;
    double q = r/h;
    double prefactor;
    if (q >= 2.){
        prefactor = 1./(r*r);
    }
    else if (q < 2. && q >= 1.){
        prefactor = (8.*q/3.  - 3.*q*q + 6.*q*q*q/5. - q*q*q*q/6. - 1./(15*q*q))/(h*h);
    }
    else{
        prefactor = (4.*q - 6.*q*q*q/5. + 0.5*q*q*q*q)/(h*h);
    }

    gravity.x = prefactor*dx/r;
    gravity.y = prefactor*dy/r;
    gravity.z = prefactor*dz/r;
    return (gravity);
}


void gravityinteract_calculate_acceleration(){
    struct vec3d dpsi;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if (i==j){
                continue;
            }
            else{
                double dx = particles[i].x - particles[j].x;
                double dy = particles[i].y - particles[j].y;
                double dz = particles[i].z - particles[j].z;
                double r = sqrt(dx*dx + dy*dy + dz*dz);
                double h_ij = 0.5*(particles[i].h + particles[j].h);
                dpsi = kernel_gravity_gradient(dx, dy, dz, r, h_ij);
                
                particles[i].ax -= 0.5*G*particles[j].m*dpsi.x;
                particles[i].ay -= 0.5*G*particles[j].m*dpsi.y;
                particles[i].az -= 0.5*G*particles[j].m*dpsi.z;
            }
        }
    }
}


