#ifndef KERNEL_H
#define KERNEL_H

struct vec3d{
    float x;
    float y;
    float z;
};

// smooting kernel function
float kernel_function(float r, float h);

// gradient of smoothing kernel
struct vec3d kernel_vec_gradient(float dx, float dy, float dz, float r, float h);

// laplacian of smoothing kernel
struct vec3d kernel_vec_laplacian(float dx, float dy, float dz, float r, float h);

#endif
