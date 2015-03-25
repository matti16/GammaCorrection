#include "../headers/gamma.h"

void gamma_correct(int* pixels, int size, float a, float gamma){
	int i;
	#pragma omp parallel for private(i)
	for (i=0; i<size; i++){
		pixels[i] = (int) ( a * ( pow( (double)pixels[i], (double)gamma ));
	}

	

}