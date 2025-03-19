#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int rank, numranks;

void sendrecv1(int *data, int DATACOUNT, int sendpartner, int recvpartner) {
  MPI_Send(data, DATACOUNT, MPI_INT, sendpartner, 0, MPI_COMM_WORLD);
  printf("Rank %d sent data to %d\n", rank, sendpartner);
  MPI_Recv(data, DATACOUNT, MPI_INT, recvpartner, 0, MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);
  printf("Rank %d received data from %d\n", rank, recvpartner);
}
void sendrecv2(int *data, int DATACOUNT, int sendpartner, int recvpartner) {
  for (int i=0;i<numranks;++i) {
    if (i==sendpartner) {
      MPI_Send(data, DATACOUNT, MPI_INT, sendpartner, 0, MPI_COMM_WORLD);
      printf("Rank %d sent data to %d\n", rank, sendpartner);
    }
    if (i==rank) {
      MPI_Recv(data, DATACOUNT, MPI_INT, recvpartner, 0, MPI_COMM_WORLD,
                MPI_STATUS_IGNORE);
      printf("Rank %d received data from %d\n", rank, recvpartner);
    }
  }
}

int main(int argc,char **argv) {
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numranks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  //const int DATACOUNT=1024;
  const int DATACOUNT=768;
  int data[DATACOUNT];
  for (int i=0;i<DATACOUNT;++i) {
    data[i] = i*(numranks+rank);
  }
  const int sendpartner = (rank)? rank-1 : numranks-1;
  //const int recvpartner = (rank==numranks-1)? 0 : rank+1;
  const int recvpartner = sendpartner;
  printf("Rank %d=>%d and %d<=%d\n", rank, sendpartner, rank, recvpartner);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  sendrecv1(data, DATACOUNT, sendpartner, recvpartner);
  //sendrecv2(data, DATACOUNT, sendpartner, recvpartner);
  MPI_Finalize();
  return 0;
}
