#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "matrix.h"
#include "log.h"

pthread_t *ids;
double somaTotal;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

/**
 * Input matrix 1
 */
matrix* mat1;

/**
 * Input matrix 2
 */
matrix* mat2;

/**
 * Result matrix
 */ 
matrix* result;

/**
 * Average of the values in the result matrix
 */
double average;

/**
 * Number of workers
 */
unsigned nworkers;

/**
 * Funtion to be executed by each thread
 */
void* worker_function(void* arg) {

    // do not place any code before this call to function fsolog
    fsolog("starting");
    int length_thread = mat1->nrows/nworkers;
    int start = length_thread*(int)(long)arg;
	int end = start + length_thread;
    unsigned range[2] = {start, end};
    matrix* matriz = submat(mat1, range);
    matrix* matriz_multiplicacao = mat_mul(matriz, mat2);

    // TODO -- compute part of the matrix multiplication, and place it in global variable result

    for(int i = start; i<end; i++) {
        for(int j =0; j<result->ncols; j++) {
            pthread_mutex_lock(&m);
            somaTotal += matriz_multiplicacao->data[i-start][j];
            pthread_mutex_unlock(&m);
            result->data[i][j] = matriz_multiplicacao->data[i-start][j];
        }
    }

    // TODO -- compute the average and place in global variable average
    // Just one thread must cumpute de average
    pthread_barrier_wait(&barrier); 
    if((int)(long)arg == 0) {
        average = somaTotal/(result->ncols*result->nrows);
    }
    
    // do not place any code after this call to function fsolog
    fsolog("done");
    return NULL;
}

/**
 * Compute the matrix multiplication result = mat1 * mat2
 * and the average value of the result matrix  
 */
double par_matmul_average(const unsigned nworkers) {
    // TODO -- launch the workers++
    ids = (pthread_t *)malloc(nworkers*sizeof(pthread_t));
    int i;
    pthread_barrier_init(&barrier, NULL, nworkers);
    for(i = 0; i<nworkers; i++) {
        pthread_create(&ids[i], NULL, worker_function, (void*)(long)i);
    }
    for ( i = 0; i < nworkers; i++){
        pthread_join(ids[i], NULL);
    }
    
    return average;
}


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
    nworkers = strtol(argv[4], NULL, 10);

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
    mat1 = new_mat(nrows1, ncols1);
    mat2 = new_mat(ncols1, ncols2);

	// You may use fill_mat or fill_mat_value in your experiments
    fill_mat_random(mat1);
	fill_mat_random(mat2);


#ifdef VERBOSE
	print_mat(mat1);
	print_mat(mat2);
#endif

    result = new_mat(nrows1, ncols2);

    double average;
    if ((average = par_matmul_average(nworkers)) < 0) {
        perror("");
        return 1;
    }

	// print the result matrix
    print_mat(result);
    
    // print the average
 	printf ("Average %f\n",  average);

	// cleanup
	free_mat(mat1);
	free_mat(mat2);
	free(result);

	return 0;
}