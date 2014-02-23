#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "boundaries.h"

float k0 = 1.;
float rho0 = 1.;
float gamma = 1.;

float eos_calculate_pressure(float rho, float k0, float rho0, float gamma){
    return k0*(pow((rho/rho0), gamma) - 1.);
}

