// https://github.com/mpitutorial/mpitutorial/
// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// Example using MPI_Send and MPI_Recv to pass a message around in a ring.
//
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int ring(const int rank,const int size,int token) {
  if (rank) {
    MPI_Recv(&token, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Process %d received token %d from process %d\n", rank, token,
           rank - 1);
  }
  ++token;
  MPI_Send(&token, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD);
  if (!rank) {
    MPI_Recv(&token, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received token %d from process %d\n", rank, token,
           size-1);
  }
  return token;
}

int main(int argc,char **argv) {
  MPI_Init(&argc, &argv);
  int rank, size, token = -1;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  for (int i=0;i<10;++i) {
    token = ring(rank, size, token);
  }
  MPI_Finalize();
  return 0;
}
