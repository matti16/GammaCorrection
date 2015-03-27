# GammaCorrection

Use MPI (+OpenMP) to implement a parallel version of the gamma correction image enhancement algorithm for grayscale images. Use the image format you prefer ("pgm - portable graymap" is an easy to parse grayscale format). The code has to be demonstrated using at least two physical machines connected in a LAN (with or without additional virtual machines to emulate a larger cluster).


Compile with ```mpicc```:

```mpicc -fopenmp -std=c99 *.c -lm```


Run with ```mpirun```:

```mpirun -np 4 a.out ../images/sample.pgm 1 3```