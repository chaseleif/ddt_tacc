#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

float compute(int rank,int *numranks) {
  return (float)rank/(*numranks);
}

int main(int argc,char **argv) {
  MPI_Init(&argc,&argv);
  int rank, numranks;
  MPI_Comm_size(MPI_COMM_WORLD, &numranks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank&1)
    printf("Rank %d result = %f\n", rank, compute(rank, numranks));
  else
    printf("Rank %d result = %f\n", rank, compute(rank, &numranks));
  MPI_Finalize();
  return 0;
}
