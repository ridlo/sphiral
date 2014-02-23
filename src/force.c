#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "kernel.h"
#include "eos.h"
#include "boundaries.h"
#include "force.h"

force_calc_acceleration(){
    // without NNPS - LOL
    int i=0;
    for (i=0; i<N; i++){
        compute_DensityPressure();
    }

    compute_acceleration(){

