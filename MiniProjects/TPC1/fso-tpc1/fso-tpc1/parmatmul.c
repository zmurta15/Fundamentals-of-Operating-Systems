#include "parmatmul.h"

#include <sys/types.h>
#include <sys/wait.h>

/**
 * Reads a matrix from the channel with descriptor 'fd'
 * directly to matrix 'mat', starting at row 'first_row' 
 */
matrix* read_mat_into(int fd, matrix* mat, const unsigned first_row) {
    int rows;
    read(fd, &rows, sizeof(unsigned));   // read number of rows
    
    int colums;
    read(fd, &colums, sizeof(unsigned)); // read number of cols
    
	for(int i = first_row; i<first_row + rows; i++)     // read matrix data from pipe, row by row, into matrix 'mat' starting at row 'first_row'
        read(fd, mat->data[i], sizeof(int) * colums);

    return mat;
}

/**
 * Writes matrix 'mat' to the channel with descriptor 'fd'
 * 
 *  Returns 0, if everything went ok
 *         -1, if an error ocurred
 */
int write_mat(const int fd, const matrix* mat) {
    write(fd, &mat->nrows, sizeof(unsigned));
    write(fd, &mat->ncols, sizeof(unsigned));

    for (int i = 0; i < mat->nrows; i++)
        write(fd,  mat->data[i], sizeof(int) *  mat->ncols);

    return 0;
}

/**
 * Creates the pipe to receive the result from worker 'worker'.
 * Creates a process to run the code of worker 'worker'
 * Matrices 'mat1' and 'mat2' are the input matrices for the multiplication. 
 *
 * Returns the pid of worker, if everything went ok
 *         -1, if an error ocurred
 */
int launch_worker(worker_t* worker, const matrix* mat1, const matrix* mat2) {
    pipe(worker->pipe_sm); // create pipe
    
    int d1 = worker->pipe_sm[1];
    int d0 = worker->pipe_sm[0];
    
    
    int pid = fork(); // create worker

    if(pid ==-1) 
        abort();
    if(pid == 0) {
        // worker: 
        // obtain submatrix assigned to it: see function submat of the matrix module
        // compute the matrix multiplication: see funtion mat_mult of the matrix module
        // send result to the master: see funtion write_mat
        close(d0); //close the read end of the pipe
        matrix* matrx = submat(mat1, worker->range);
        matrix* matmultiplication = mat_mul(matrx, mat2);
        write_mat(worker->pipe_sm[1], matmultiplication);
        exit(0);
    }
    else {
        close(d1); //close the write end of the pipe
    }
    return pid;
    // master:
        // send pid of the worker or error
}



int par_matmul(const matrix* mat1, const matrix* mat2, worker_t workers[], const unsigned nworkers) {

    printf ("Master launching %d workers\n",  nworkers);
    
    const unsigned rows_per_worker = mat1->nrows/nworkers;
    for (unsigned i = 0; i < nworkers; i++) {
        workers[i].id = i;
        workers[i].range[0] = i * rows_per_worker;
        workers[i].range[1] = workers[i].range[0] + rows_per_worker;

        if ((workers[i].pid = launch_worker(&workers[i], mat1, mat2)) < 0) 
            return workers[i].pid;
    }

    return 0;
}


void get_result_matrix(matrix* result, worker_t workers[], const unsigned nworkers) {
    // wait for the results
    for (unsigned i = 0; i < nworkers; i++) {
        read_mat_into(workers[i].pipe_sm[0], result, workers[i].range[0]);
        printf ("Master received result from worker %d\n",  workers[i].id);
        wait(NULL);
    }
}
