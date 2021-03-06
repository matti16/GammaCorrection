#ifndef GAMMA_H
#define GAMMA_H
#include <math.h>
#include <omp.h>


extern void gamma_correct(int* pixels, int size, float a, float gamma);

extern void single_gamma(int* value, float a, float gamma);

#endif
