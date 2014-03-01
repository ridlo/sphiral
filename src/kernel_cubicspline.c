#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "problem.h"
#include "force.h"
#include "kernel.h"

double tensil_correction = 0.666666666666667;

// Piecewise Cubic Spline: Monaghan and Lattanzio (1985)
double kernel_function(double r, double h){
    double q = r/h;
    double alpha = 3./(2.*M_PI*h*h*h);
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

struct vec3d kernel_vec_gradient(double dx, double dy, double dz, double r, double h){
    struct vec3d grad;
    double q = r/h;
    double alpha = 3./(2.*M_PI*h*h*h);
    double prefactor;
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

// ra guno
/*
struct vec3d kernel_vec_laplacian(double dx, double dy, double dz, double r, double h){
    double q = r/h;
    double alpha = 3./(2.*M_PI*h*h*h);// 3D
    double prefactor;
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
