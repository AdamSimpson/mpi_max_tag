#include "stdio.h"
#include "mpi.h"

int main(int argc, char**argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 2) {
        printf("Use two ranks!\n");
        exit(1);
    }

    if(rank == 0)
        printf("Maximum tag size defined by MPI_TAG_UB: %d\n", MPI_TAG_UB);

    char send_buff = 1;
    char recv_buff = 0;

    MPI_Request req;

    int i;
    for(i=0; i<2147483647; i++)
    {
	int tag = i;
        if(rank==1) {
            MPI_Irecv(&recv_buff, 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &req);
            MPI_Wait(&req, MPI_STATUS_IGNORE);
            printf("Tag: %d\n", tag);
        }
        if(rank==0) {
    	    MPI_Isend(&send_buff, 1, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &req);
            MPI_Wait(&req, MPI_STATUS_IGNORE);
        }
    }

    return 0;
}
