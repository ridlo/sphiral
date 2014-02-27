#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "problem.h"
#include "force.h"
#include "kernel.h"

float tensil_correction = 0.666666666666667;

// Piecewise Cubic Spline: Monaghan and Lattanzio (1985)
// ! Need tensil correction -> 2/3
// r is distance 
float kernel_function(float r, float h){
    float q = r/h;
    float alpha = 3./(2.*M_PI*h*h*h);
    if (q >= 2.){
        return 0.;
    }
    else if (q < 2. && q >= 1.){
        return alpha*pow((2. - q), 3)/6.;
    }
    else{
        return alpha*(0.666666666666667 - q*q + 0.5*q*q*q);
    }
}

// partial{f}/partial{r} in direction of r
struct vec3d kernel_vec_gradient(float dx, float dy, float dz, float r, float h){
    struct vec3d grad;
    float q = r/h;
    float alpha = 3./(2.*M_PI*h*h*h);
    float prefactor;
    if (q >= 2.){
        prefactor = 0;
    }
    else if (q < 2. &&  q >= 1.){
        prefactor = alpha*0.5*(2-q)*(2-q)/h;
    }
    else{
        prefactor = alpha*q*(-2 + 1.5*q)/h;
    }

    grad.x = prefactor*dx/r; 
    grad.y = prefactor*dy/r;
    grad.z = prefactor*dz/r;
    return (grad);
}

struct vec3d kernel_gravity_gradient(float dx, float dy, float dz, float r, float h){
    struct vec3d gravity;
    float q = r/h;
    float prefactor;
    if (q >= 2){
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

// ra guno
/*
struct vec3d kernel_vec_laplacian(float dx, float dy, float dz, float r, float h){
    float q = r/h;
    float alpha = 3./(2.*M_PI*h*h*h);// 3D
    float prefactor;
    if (q >= 2.){
        prefactor = 0;
    }
    else if (q < 2. && q >= 1.){
        prefactor = alpha*(-4./(h*r) + 6./(h*h) - 2.*r/(h*h*h));
    }
    else{
        prefactor = alpha*(-6./(h*h) + 6.*r/(h*h*h));
    }

    struct vec3d laplacian;
    laplacian.x = prefactor*dx/r;
    laplacian.y = prefactor*dy/r;
    laplacian.z = prefactor*dz/r;
   
    return laplacian;
}
*/
