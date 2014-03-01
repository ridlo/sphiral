#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "boundaries.h"
#include "problem.h"

double G = 1.;
// constant of gravity (for simulation on "Earth")
double gravity_constant = 9.8;

void gravityinteract_calculate_accceleration(){
    particles[i].ax += 0.;
    particles[i].ay += gravity_constant;
    particles[i].az += 0.;
}
