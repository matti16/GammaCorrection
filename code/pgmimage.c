#include "../headers/pgmimage.h"

int* load(char* filename, t_pgm* img, int num_tasks, int* length){
	FILE* fin = NULL;
	//Try to open file
	fin=fopen(filename, "r");
	if(fin == NULL){
		printf("Error opening file!\n");
		exit(-1);
	}
	//Check format
	char magic[2];
	fscanf(fin, "%s", magic);
	if(strcmp(magic, "P2")){
		printf("Incorrect image format!\n");
		fclose(fin);
		exit(-1);
	}
	
	//Retrieve image information
	int width, height, max;
	fscanf(fin, "%d", &width);
	fscanf(fin, "%d", &height);
	fscanf(fin, "%d", &max);
	img->max = max;
	img->height = height;
	img->width = width;

	int size = width*height;
	int diff = (size/num_tasks) * num_tasks;
	int* pixels;

	if(diff == size){
		pixels = (int*) malloc(sizeof(int)*size);
		*(length) = size;
	}else{
		diff = (size/num_tasks)*(num_tasks+1);
		pixels = (int*) malloc(sizeof(int)*diff);
		*(length) = diff;
	}

	int i, pixel;
	for(i=0; i<size; i++){
		fscanf(fin, "%d", &pixel);
		pixels[i] = pixel;
	}
	for(; i<diff; i++){
		pixels[i] = 0;
	}

	return pixels;
	
}


void store(t_pgm* img, int* pixels){
	int width = img->width;
	int height = img->height;
	int max = img -> max;
	int size = width*height;
	FILE* out = NULL;
	out = fopen("out.pgm", "w");

	if(out == NULL){
		printf("Error in creating file\n");
		exit(-1);
	}

	fprintf(out, "P2\n");
	fprintf(out, "%d %d\n", width, height);
	fprintf(out, "%d\n", max);

	int i;
	for(i = 0; i < size; i++){
		fprintf(out, "%d ", pixels[i]);
		if( (i+1) % width == 0 ){
			fprintf(out, "\n");
		}
	}

	fclose(out);
}
