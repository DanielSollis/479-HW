#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int rank, size;
	MPI_Request ireq;
	MPI_Request newreq;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	double start = MPI_Wtime();
	double number = 1.5;
	if (rank == 0) {
		MPI_Isend(&number, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &ireq);
		MPI_Wait(&ireq, &status);
		MPI_Irecv(&number, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &newreq);
		
	}
	else if (rank == 1) {
		MPI_Irecv(&number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &ireq);
		MPI_Wait(&ireq, &status);
		long double firstEnd = MPI_Wtime();
		MPI_Isend(&number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &newreq);
		MPI_Wait(&newreq, &status);
		long double firstTotal = firstEnd - start;
		printf("the first transmission took: %Le\n", firstTotal);
		long double secondEnd = MPI_Wtime();
		long double secondTotal = secondEnd - start;
		printf("the second transmission took %Le\n", secondTotal);
	}
	MPI_Finalize();
	return 0;
}
