#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "particle.h"
#include "main.h"
#include "tools.h"

/* used for speedup */
double tools_normaldistribution_rsq;
double tools_normaldistribution_v2;
int tools_normaldistribution_ready = 0;

double tools_uniform(double min, double max){
    return ((double)rand())/((double)(RAND_MAX))*(max-min) + min;
}

double tools_normal(double variance){
    if (tools_normaldistribution_ready == 1){
        tools_normaldistribution_ready = 0;
        return tools_normaldistribution_v2*sqrt(-2.*log(tools_normaldistribution_rsq)/tools_normaldistribution_rsq*variance);
    }

    double v1, v2, rsq=1.0;
    while (rsq>=1. || rsq<1.0e-12){
        v1 = 2.*((double)rand())/((double)RAND_MAX) - 1.0;
        v2 = 2.*((double)rand())/((double)RAND_MAX) - 1.0;
        rsq = v1*v1 + v2*v2;
    }

    tools_normaldistribution_ready = 1;
    tools_normaldistribution_rsq = rsq;
    tools_normaldistribution_v2 = v2;
    return v1*sqrt(-2.*log(rsq)/rsq*variance);
}

