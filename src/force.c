#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "kernel.h"
#include "problem.h"
#include "boundaries.h"
//#include "gravityinteract.h"
#include "force.h"


float kappa = 2.; // scaling factor for NNP

float cs = 0.01; // speed of the sound
float rho0;
float Kc;

float eta        = 1.2; // dynamic h constant 1.2 < eta < 1.5 Rosswog 2009

float alpha_visc = 1.;
float beta_visc  = 2.;
float epsi       = 0.01; // softening in artificial viscosity equation


/* equation of state --------------------------- */
// float B = 1.; // initial pressure
float K = 0.015;
float gam = 2;


int *pair_i; // contain the indices of the particles in the interacting pair
int *pair_j;
int pair_max = 0;

float *w; // smoothing/kernel function 
struct vec3d *dw; // gradient of kernel

// liquid
/*
float eos_calculate_pressure(float rho){
    return B*(pow((rho/rho0), gamma) - 1.);
}
*/
// c^2 = dP/drho = B*gamma*(rho^(gamma-1))/(rho^gamma)
// c0^2 = B*gamma*/rho0 

// polytrop
float eos_calculate_pressure(float rho){
    return K*pow(rho, gam);
}


/* acceleration -------------------------------- */
void force_calc_acceleration(){
    int i, j, k;
    
    // restart acceleration
    for (i=0; i<N; i++){
        particles[i].ax = 0.;
        particles[i].ay = 0.;
        particles[i].az = 0.;
    }

    // update h -> it should be coupled with change in density (solve with Newton Raphson)
    for (i=0; i<N; i++){
        particles[i].h = eta*pow((particles[i].m/particles[i].rho), 0.333333333333333);
    }

    //printf("%f ", particles[0].h);
    
    /* Interaction -------------------------- */
    // "Pairwise Interaction"
    int niac = 0; // number of the interacting pairs
    int countiac[N]; // number of the neighbouring particles for each particle
    // it can be used to control the number of NNP 
    
    // Initialization
    for (i=0; i<N; i++){
        countiac[i] = 0;
    }
    
    for (i=0; i<(N-1); i++){
        for (j=i+1; j<N; j++){
            /* effective NNPS should be here */
            // distance between i and j
            float dx = particles[i].x - particles[j].x;
            float dy = particles[i].y - particles[j].y;
            float dz = particles[i].z - particles[j].z;
            float r = sqrt(dx*dx + dy*dy + dz*dz); // distance
            
            float h_ij = 0.5*(particles[i].h + particles[j].h);
            
             
            // simple NNP: "All-pair search" 
            if (r <= kappa*h_ij){
                // alocate memory of pairs
                while (pair_max <= niac){
                    pair_max += 128;
                    pair_i = realloc(pair_i, pair_max*sizeof(int));
                    pair_j = realloc(pair_j, pair_max*sizeof(int));
                    w      = realloc(w, pair_max*sizeof(float));
                    dw     = realloc(dw, pair_max*sizeof(struct vec3d));
                }
                pair_i[niac] = i;
                pair_j[niac] = j;
                countiac[i] = countiac[i] + 1; 
                countiac[j] = countiac[j] + 1;

                // calculate smoothing function and derivative
                w[niac] = kernel_function(r, h_ij);
                dw[niac] = kernel_vec_gradient(dx, dy, dz, r, h_ij);

                niac = niac+1;
            }
        }
    }
    
    /* calculate rho and average */
    // self contribution
    float total_rho = 0.;
    for (i=0; i<N; i++){
        particles[i].rho = particles[i].m*kernel_function(0., particles[i].h);
        total_rho += particles[i].rho;
    }
    rho0 = total_rho/N;
    Kc = rho0*cs*cs;
    
    //printf("%f %f\n", particles[0].rho, Kc);

    // Nighbors contribution
    for (k=0; k<niac; k++){
        i = pair_i[k];
        j = pair_j[k];
        particles[i].rho += particles[j].m*w[k];
        particles[j].rho += particles[i].m*w[k];
    }

    /* calculate pressure contribution */
    // self pressure from Equation od State
    for (i=0; i<N; i++){
        particles[i].P = eos_calculate_pressure(particles[i].rho);
    }

    // acceleration from pressure gradient and viscosity term
    for (k=0; k<niac; k++){
        i = pair_i[k];
        j = pair_j[k];
        float factor_P, factor_v, precalc;
        
        // pressure gradient term
        factor_P = particles[i].P/(particles[i].rho*particles[i].rho) + particles[j].P/(particles[j].rho*particles[j].rho);
        
        // viscosity term (PI_ab)
        // dot product v_ij & r_ij
        /*
        float dotvr = 0;
        float dvx = particles[i].vx - particles[j].vx;
        float dvy = particles[i].vy - particles[j].vy;
        float dvz = particles[i].vz - particles[j].vz;
        float dx  = particles[i].x - particles[j].x;
        float dy  = particles[i].y - particles[j].y;
        float dz  = particles[i].z - particles[j].z;
        float r_square   = dx*dx + dy*dy + dz*dz;
        dotvr = dvx*dx + dvy*dy + dvz*dz;
        if (dotvr >= 0)
            factor_v = 0.;
        else{    
            float h_ij   = 0.5*(particles[i].h + particles[j].h);
            float rho_ij = 0.5*(particles[i].rho + particles[j].rho);
            float c_ij   = 0.5*(sqrt(Kc/particles[i].rho) + sqrt(Kc/particles[j].rho)); // liquid
            // c_ij = cs
            float psi_ij = h_ij*dotvr/(r_square + epsi*h_ij*h_ij); // eta -> softening term prevent a singularity when r_ab=0
            factor_v = (-alpha_visc*c_ij*psi_ij + beta_visc*psi_ij*psi_ij)/rho_ij;
        }
        */
        factor_v = 0;
        precalc = factor_P + factor_v;// + tensil_correction;
        
        // for i
        particles[i].ax -= particles[j].m*precalc*dw[k].x;
        particles[i].ay -= particles[j].m*precalc*dw[k].y;
        particles[i].az -= particles[j].m*precalc*dw[k].z;

        // and for j
        particles[j].ax -= particles[i].m*precalc*dw[k].x;
        particles[j].ay -= particles[i].m*precalc*dw[k].y;
        particles[j].az -= particles[i].m*precalc*dw[k].z;
    }

    /* acceleration from gravity term --------------------------- */
    // using constant gravity
    // gravityinteract_calculate_acceleration();
    
    // using gravity kernel
    // direct method
    struct vec3d dpsi;
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            if (i==j){
                continue;
            }
            else{
                float dx = particles[i].x - particles[j].x;
                float dy = particles[i].y - particles[j].y;
                float dz = particles[i].z - particles[j].z;
                float r = sqrt(dx*dx + dy*dy + dz*dz); // distance
                float h_ij = 0.5*(particles[i].h + particles[j].h);
                dpsi = kernel_gravity_gradient(dx, dy, dz, r, h_ij);
                particles[i].ax -= 0.5*G*particles[j].m*dpsi.x;
                particles[i].ay -= 0.5*G*particles[j].m*dpsi.y;
                particles[i].az -= 0.5*G*particles[j].m*dpsi.z;
            }
        }
    }
    
}

