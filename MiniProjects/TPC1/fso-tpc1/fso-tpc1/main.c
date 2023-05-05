#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "parmatmul.h"
#include "matrix.h"


void usage(char* prog) {
    printf("usage: %s nrows1 ncols1 ncols2 nworkers [seed]\n", prog);
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
    const unsigned seed = argc == 6 ? strtol(argv[5], NULL, 10) : 1;
	srand(seed);

	// create and fill matrices
    matrix* mat1 = new_mat(nrows1, ncols1);
    matrix* mat2 = new_mat(ncols1, ncols2);

	// You may use fill_mat or fill_mat_value in your experiments
    fill_mat_random(mat1);
	fill_mat_random(mat2);




#ifdef VERBOSE
	print_mat(mat1);
	print_mat(mat2);
#endif

	// create and launch workers
    worker_t workers[nworkers];

    if (par_matmul(mat1, mat2, workers, nworkers) < 0) {
        perror("");
        return 1;
    }

    matrix* result = new_mat(nrows1, ncols2);

    // get the result matrix
	get_result_matrix(result, workers, nworkers);

	// print result matrix
    print_mat(result);

	// cleanup
	free_mat(mat1);
	free_mat(mat2);
	free(result);

	return 0;
}