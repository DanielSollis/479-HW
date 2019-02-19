#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int size, rank;
	MPI_Request ireq;
	MPI_Status istat;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int token;
	long double start = MPI_Wtime();
	if (rank != 0) {
		MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%d recieved the message\n", rank);
	}
	else {
		//set token's value if you are rank 0
		token = -1;
	}
	MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
	//now process 0 can receive from the last process
	if (rank == 0) {
		MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		long double end = MPI_Wtime();
		long double total = end - start;
		printf("0 recieved the message\n");
		printf("token circulation took %Le\n", total);
	}
	MPI_Finalize();
	return 0;
}
