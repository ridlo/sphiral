#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "problem.h"
#include "kernel.h"
#include "eos.h"
#include "gravityinteract.h"
#include "force.h"

double kappa      = 2.; // scaling factor for NNP
double eta        = 1.2; // dynamic h constant 1.2 < eta < 1.5 Rosswog 2009

double alpha_visc = 1.;
double beta_visc  = 2.;
double epsi       = 0.01; // softening in artificial viscosity equation

int *pair_i; // contain the indices of the particles in the interacting pair
int *pair_j;
int pair_max = 0;

double *w; // smoothing/kernel function 
struct vec3d *dw; // gradient of kernel

/* update h ----------------------------- */
void update_h(){
    for (int i=0; i<N; i++){ // other method: using Newton Raphson or constant number of neighbour
        particles[i].h = eta*pow((particles[i].m/particles[i].rho), 0.333333333333333);
        //printf("%lf", particles[i].h);
    }
}

/* acceleration -------------------------------- */
void force_calc_acceleration(){
    for (int i=0; i<N; i++){
        particles[i].ax = 0.;
        particles[i].ay = 0.;
        particles[i].az = 0.;
    }
    
    // starting with constant h (?)

    /* Interaction -------------------------- */
    // "Pairwise Interaction"
    int niac = 0; // number of the interacting pairs
    int countiac[N]; // number of the neighboring particles for each particle, it can be used to control the number of NNP     
        
    for (int i=0; i<N; i++) // Initialization
        countiac[i] = 0;
    
    //printf("nice\n");
    for (int i=0; i<(N-1); i++){
        for (int j=i+1; j<N; j++){
            /* effective NNPS should be here */
            // simple NNP: "All-pair search" 
            
            double dx = particles[i].x - particles[j].x;
            double dy = particles[i].y - particles[j].y;
            double dz = particles[i].z - particles[j].z;
            double r = sqrt(dx*dx + dy*dy + dz*dz); // distance between i & j

            double h_ij = 0.5*(particles[i].h + particles[j].h);
             
            if (r <= kappa*h_ij){
                while (pair_max <= niac){ // alocate memory for pairs
                    pair_max += 128;
                    pair_i = realloc(pair_i, pair_max*sizeof(int));
                    pair_j = realloc(pair_j, pair_max*sizeof(int));
                    w      = realloc(w, pair_max*sizeof(double));
                    dw     = realloc(dw, pair_max*sizeof(struct vec3d));
                }

                pair_i[niac] = i;
                pair_j[niac] = j;
                countiac[i] = countiac[i] + 1; 
                countiac[j] = countiac[j] + 1;

                // calculate smoothing function and derivative
                w[niac] = kernel_function(r, h_ij);
                dw[niac] = kernel_vec_gradient(dx, dy, dz, r, h_ij);

                niac++;
            }
        }
    }
    //printf("lol\n");

    
    /* update density ----------------------- */
    for (int i=0; i<N; i++){ // self contribution
        particles[i].rho = particles[i].m*kernel_function(0., particles[i].h);
    }
    
    for (int k=0; k<niac; k++){ // Nighbors contribution
        int i = pair_i[k];
        int j = pair_j[k];
        particles[i].rho += particles[j].m*w[k];
        particles[j].rho += particles[i].m*w[k];
    }

    
    // @TODO normalized density - modified

    // Drho/dt
    
    // De/dt

    /* update internal energy --------------- */


    /* update pressure ---------------------- */
    eos_calculate_pressure(); // from Equation of State
    
    /* update sound of speed ---------------- */
    eos_calculate_speedofsound();

    /* acceleration from pressure gradient and viscosity term --------------- */
    for (int k=0; k<niac; k++){
        int i = pair_i[k];
        int j = pair_j[k];
        double factor_P;
        double factor_v;
        double precalc;
        
        // pressure gradient term 
        //factor_P = 2.*sqrt(particles[i].P*particles[j].P)/(particles[i].rho*particles[j].rho);
        factor_P = particles[i].P/(particles[i].rho*particles[i].rho) + particles[j].P/(particles[j].rho*particles[j].rho);
        
        // viscosity term
        double dotvr; // dot product v_ij & r_ij
        double dvx = particles[i].vx - particles[j].vx;
        double dvy = particles[i].vy - particles[j].vy;
        double dvz = particles[i].vz - particles[j].vz;
        double dx  = particles[i].x - particles[j].x;
        double dy  = particles[i].y - particles[j].y;
        double dz  = particles[i].z - particles[j].z;
        double r_square   = dx*dx + dy*dy + dz*dz;
        dotvr = dvx*dx + dvy*dy + dvz*dz;
        if (dotvr >= 0)
            factor_v = 0.;
        else{    
            double h_ij   = 0.5*(particles[i].h + particles[j].h);
            double rho_ij = 0.5*(particles[i].rho + particles[j].rho);
            double c_ij   = 0.5*(particles[i].c + particles[j].c); 
            double psi_ij = h_ij*dotvr/(r_square + epsi*h_ij*h_ij); 
            factor_v = (-alpha_visc*c_ij*psi_ij + beta_visc*psi_ij*psi_ij)/rho_ij;
        }
        
        precalc = factor_P + factor_v; // + tensil_correction; // tensil correction from kernel function
        
        particles[i].ax -= particles[j].m*precalc*dw[k].x;
        particles[i].ay -= particles[j].m*precalc*dw[k].y;
        particles[i].az -= particles[j].m*precalc*dw[k].z;
        
        particles[j].ax += particles[i].m*precalc*dw[k].x;
        particles[j].ay += particles[i].m*precalc*dw[k].y;
        particles[j].az += particles[i].m*precalc*dw[k].z;
    }
    
    /* acceleration from gravity interaction ------------ */
    gravityinteract_calculate_acceleration();
    
    update_h();
}

