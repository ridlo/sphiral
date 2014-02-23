#ifndef KERNEL_H
#define KERNEL_H

// smooting kernel function
float kernel_function(float r, float h);

// gradient of smoothing kernel
float kernel_gradient(float r, float h);

// laplacian of smoothing kernel
float kernel_laplacian(float r, float h);

#endif
