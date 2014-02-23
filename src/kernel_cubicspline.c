#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "problem.h"

// Piecewise Cubic Spline: Monaghan and Lattanzio (1985)
// ! Need tensil correction -> 2/3
// r is distance 
float kernel_function(float r, float h){
    float q = r/h;
    float alpha = 3./(2.*M_PI*h*h*h);// 3D
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
float kernel_gradient(float r, float h){
    float q = r/h;
    float alpha = 3./(2.*M_PI*h*h*h);// 3D
    if (q >= 2.){
        return 0;
    }
    else if (q < 2. && > q >= 1.){
        return alpha*(-2. + 2*q - 0.5*q*q)/h;
    }
    else{
        return alpha*(-2*q + 1.5*q*q)/h;
    }
}

float kernel_laplacian(float r, float h){
    float q = r/h;
    float alpha = 3./(2.*M_PI*h*h*h);// 3D
    if (q >= 2.){
        return 0;
    }
    else if (q < 2. && > q >= 1.){
        return alpha*(-4./(h*r) + 6./(h*h) - 2.*r/(h*h*h));
    }
    else{
        return alpha*(-6./(h*h) + 6.*r/(h*h*h);
    }
}

