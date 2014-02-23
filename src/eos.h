#ifndef EOS_H
#define EOS_H

// Calculate pressure from Equation of state
float eos_calculate_pressure(float rho, float k0, float rho0, float gamma);

extern float k0;
extern float rho0;
extern float gamma;

#endif
