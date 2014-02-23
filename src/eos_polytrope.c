#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "boundaries.h"
#include "problem.h"

float k0 = 1.;
float rho0 = 1.;
float gamma = 1.;

// polytropic equation of state
float eos_calculate_pressure(float rho, float k0, float rho0, float gamma){
    return k0*pow(rho, gamma);
}

