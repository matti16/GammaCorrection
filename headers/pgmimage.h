#ifndef PGMIMAGE_H
#define PGMIMAGE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct t_pgm{
	int max;
	int width;
	int height;
}t_pgm;


extern int* load(char* filename, t_pgm* img, int num_tasks, int* length);

extern void store(t_pgm* img, int* pixels);

#endif
