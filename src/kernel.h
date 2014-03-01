#ifndef KERNEL_H
#define KERNEL_H

extern double tensil_correction;

double kernel_function(double r, double h); // smoothing kernel function

struct vec3d kernel_vec_gradient(double dx, double dy, double dz, double r, double h); // gradient of smoothing kernel

// laplacian of smoothing kernel
// struct vec3d kernel_vec_laplacian(double dx, double dy, double dz, double r, double h);

#endif
