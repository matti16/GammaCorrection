#include "../headers/pgmimage.h"

int* load(char* filename, t_pgm img, int num_tasks){
	FILE* fin = NULL;
	//Try to open file
	if(!(fin=fopen(filename, "r")){
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
	fscanf(fin, "%d %d %d", &widht, &height, &max);
	img->max = max;
	img->height = height;
	img->widht = widht;

	int size = widht*height;
	int diff = (size/num_tasks) * num_tasks;
	int* pixels;

	if(diff == 0){
		pixels = (int*) malloc(sizeof(int)*size);
	}else{
		diff = (size/num_tasks)*(num_tasks+1);
		pixels = (int*) malloc(sizeof(int)*diff);
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


void store(t_pgm img, int* pixels){
	int widht = img->widht;
	int height = img->height
	int size = widht*height;
	FILE* out = NULL;
	out = fopen("out.pgm", "w");

	if(out == NULL){
		printf("Error in creating file\n");
		exit(-1);
	}

	fprintf(out, "P2\n");
	fprintf(out, "%d %d\n", width, height);
	fprintf(out, "%d\n", img.max);

	int i;
	for(i = 0; i < length; i++){
		fprintf(out, "%d ", get(img, i));
		if( (i+1) % width == 0 ){
			fprintf(out, "\n");
		}
	}

	fclose(out);
}