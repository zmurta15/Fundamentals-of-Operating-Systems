#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "parmatmultcp.h"
#include "matrix.h"
#include "tcp_comm.h"


void usage(char* prog) {
	printf("usage: %s nrows1 ncols1 ncols2 nworkers tcp_port [seed]\n", prog);
}

int main(int argc, char* argv[]) {

	// check and get the command line parameters
	if (argc < 5 || argc > 7) {
		usage(argv[0]);
		return 1;	
	}

	const unsigned nrows1 = strtol(argv[1], NULL, 10);
	const unsigned nworkers = strtol(argv[4], NULL, 10);

	if ((nworkers < 1) || (nrows1 % nworkers) != 0) { 
		printf("The number of rows of matrix 1 must be a multiple of the number of workers.\n");
		usage(argv[0]);
		return 1;
	}

	const unsigned ncols1 = strtol(argv[2], NULL, 10);
	const unsigned ncols2 = strtol(argv[3], NULL, 10);

	// setup random number generator
	// const unsigned seed = argc == 7 ? strtol(argv[6], NULL, 10) : 1;
	//srand(seed);

	// create and fill matrices
	matrix* mat1 = new_mat(nrows1, ncols1);
	matrix* mat2 = new_mat(ncols1, ncols2);

	// You may use fill_mat or fill_mat_value in your experiments
	// fill_mat_random(mat1);
	// fill_mat_random(mat2);
	fill_mat_value(mat1, 2);
	fill_mat_value(mat2, 1);

#ifdef VERBOSE
	print_mat(mat1);
	print_mat(mat2);
#endif

	// create and launch workers
	int tcp_port = atoi(argv[5]);
	
	int master_socket;

	// Create socket for accepting connections from workers
	if( (master_socket = myServerSocket(tcp_port)) < 0 )
		exit(1);
#ifdef VERBOSE
	printf("tcp_port:%d master_socket:%d\n", tcp_port,master_socket);
	
#endif

	worker_t workers[nworkers]; 

	if (par_matmul(mat1, mat2, workers, nworkers, "localhost", tcp_port) < 0) {
     	perror("Error in par_matmul");
		return 1;
	}

    matrix* result = new_mat(nrows1, ncols2);

     // get the result matrix
	get_result_matrix(result, workers, nworkers, master_socket);

	// print result matrix
	printf("Result matrix: \n");
	print_mat(result);

	// cleanup
	free_mat(mat1);
	free_mat(mat2);
	free(result);
	
	myCloseSocket(master_socket);

	return 0;

}

