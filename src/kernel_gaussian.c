#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "problem.h"

// Gaussian kernel
// ! Need tensil correction -> sqrt(2)/2 = 0.70710678118
// r is distance 
float kernel_function(float r, float h){
    float q = r/h;
    float alpha = 1./(5.56832799683*h*h*h);// 3D
    if (q >= 2.){
        return 0.;
    }
    else{
        return alpha*exp(-q*q);
    }
}

// partial{f}/partial{r} in direction of r
float kernel_gradient(float r, float h){
    float q = r/h;
    float alpha = 1./(5.56832799683*h*h*h);// 3D
    if (q >= 2.){
        return 0;
    }
    else{
        return -2.*alpha*r*exp(-q*q)/(h*h);
    }
}

float kernel_laplacian(float r, float h){
    float q = r/h;
    float alpha = 1./(5.56832799683*h*h*h);// 3D
    if (q >= 2.){
        return 0;
    }
    else{
        return alpha*exp(-q*q) * (-6./(h*h) + 4.*r*r/(h*h*h*h));
    }
}

