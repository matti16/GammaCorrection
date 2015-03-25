#ifndef PGMIMAGE_H
#define PGMIMAGE_H
#include <stdlib.h>

typedef struct pgm_image{
	int max;
	int width;
	int height;
}t_pgm;


extern int* load(char* filename, t_pgm img, int num_tasks);

extern void store(t_pgm img, int* pixels);

#endif