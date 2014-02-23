#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "boundaries.h"
#include "problem.h"

// constant of gravity (for simulation on "Earth")
float gravity_constant = 0.0;

void gravity_calculate_accceleration(){
    particles[i].ax += 0.;
    particles[i].ay += gravity_constant;
    particles[i].az += 0.;
}
