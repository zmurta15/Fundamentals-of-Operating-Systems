#ifndef PARMATMUL_H
#define PARMATMUL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "matrix.h"

struct worker {
    unsigned id;  // identifier of the worker
    pid_t pid; // pid of the worker
    unsigned range[2]; // range of rows assigned to the worker
    int pipe_sm[2]; // pipe for the worker to send the results to the master
};

typedef struct worker worker_t;


/**
 * Launch 'nworkers' workers to compute the matrix multipication
 */
int par_matmul(const matrix* mat1, const matrix* mat2, worker_t workers[], const unsigned nworkers);


/**
 *  Waits for the result of the 'nworkers' workers and places it in matrix result
 */
void get_result_matrix(matrix* result, worker_t workers[], const unsigned nworkers);

#endif // PARMATMUL_H