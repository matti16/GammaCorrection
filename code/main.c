#include "../headers/pgmimage.h"
#include "../headers/gamma.h"
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>

int main(int argc, char* argv[]){
	if(argc < 4){
		printf("gamma <input-file> <A-param> <gamma>\n");
		exit(-1);
	}else if ( atof(argv[2]) <= 0 ){
		printf("<A-param> has to be greater then 0.\n");
		exit(-1);
	}
	
	int numtasks, rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	if(rank == 0){
		syslog(LOG_NOTICE, "Process %d --> Number of processes: %d\n", rank, numtasks);
	}
	
	int* pixels;
	int chunk_size;
	float a_param = atof(argv[2]);
	float gamma = atof(argv[3]);
	if(rank == 0){
		t_pgm image = (t_pgm*) malloc(sizeof(t_pgm));
		syslog(LOG_NOTICE, "Process %d --> Starting loading image..\n", rank);
		pixels = load(argv[1], image, numtasks);
		chunk_size = pixels/numtasks;
	}

	MPI_Bcast(&chunk_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

	//SCATTER
	int rcvBuffer[chunk_size];
	syslog(LOG_NOTICE, "Process %d --> Scattering\n", rank);
	MPI_Scatter(pixels, chunk_size, MPI_INT, rcvBuffer, chunk_size, MPI_INT, 0, MPI_COMM_WORLD)
	
	//CORRECT
	gamma_correct(rcvBuffer, chunk_size, a_param, gamma);

	//GATHER
	syslog(LOG_NOTICE, "Process %d --> Gathering\n", rank);
	MPI_Gather(rcvBuffer, chunk_size, MPI_INT, pixels, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

	//SAVE IMAGE
	if(rank == 0){
		syslog(LOG_NOTICE, "Process %d --> Storing\n", rank);
		store(image, pixels);
		syslog(LOG_NOTICE, "Ended\n");
	}

	closelog();
	MPI_Finalize();
	return 0;
}