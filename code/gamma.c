#include "../headers/gamma.h"

#define MAX 255

void gamma_correct(int* pixels, int size, float a, float gamma){
	int i, pixel;
	#pragma omp parallel for private(i)
	for (i=0; i<size; i++){
		pixel = (int) ( a * ( pow( (double)pixels[i], (double)gamma )));
		if(pixel > MAX){
			pixels[i] = MAX;
		}else{
			pixels[i] = pixel;
		}
	}
}

void single_gamma(int* value, float a, float gamma){
	int max;
	max = (int) ( a * ( pow( (double)(*(value)), (double)gamma )));
	if(max > MAX){
		*(value) = MAX;
	}else{
		*(value) = max;
	}
}	


