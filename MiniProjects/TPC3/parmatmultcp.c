
#include "parmatmultcp.h"

#include <sys/types.h>
#include <sys/wait.h>

#include "tcp_comm.h"

#define ERROR -1


/**
 * Reads a matrix from the channel with descriptor 'fd'
 * directly to matrix 'mat', starting at row 'first_row' 
 */
matrix* read_mat_into(int fd, matrix* mat, const unsigned first_row) {
 
	// TODO: read number of rows
	unsigned nrows;
	read(fd, &nrows, sizeof(unsigned));

	// TODO: read number of cols
	unsigned ncols;
	read(fd, &ncols, sizeof(unsigned));

	assert(ncols == mat->ncols);

	printf("Master: nrows %d ncols %d\n", nrows, ncols);

	/* read matrix data from the communication channel, row by row, 
	   into matrix 'mat' starting at row 'first_row' */
	for (int i = first_row; i < first_row + nrows; i++) {
		// myReadSocket( fd, mat->data[i], sizeof(int) * ncols);	
		if( read(fd, mat->data[i], sizeof(int) * ncols) != (sizeof(int) * ncols)) {
			printf("Unable to read row %d\n", i );
			return NULL;
		}
		#ifdef VERBOSE
		else
			printf("master: read row %d\n", i);
		#endif
	}

    return mat;
}

/**
 * Writes matrix 'mat' to the channel with descriptor 'fd'
 * 
 *  Returns 0, if everything went ok
 *         -1, if an error ocurred
 */
int write_mat(const int fd, const matrix* mat) {

	// myWriteSocket(fd, (char *)&mat->nrows, sizeof(unsigned));
	if( write(fd, &mat->nrows, sizeof(unsigned)) != sizeof(unsigned) )
		return ERROR;
		
	// myWriteSocket(fd, (char *)&mat->ncols, sizeof(unsigned));
    	if( write(fd, &mat->ncols, sizeof(unsigned)) != sizeof(unsigned) )
		return ERROR;

	for (int i = 0; i < mat->nrows; i++) {
		// TODO: send the result
		write(fd, mat->data[i], sizeof(int) * mat->ncols);
	}

    return 0;

}

/**
 * Creates all processes to run the code of worker 'worker'
 * 
 * Matrices 'mat1' and 'mat2' are the input matrices for the multiplication. 
 *
 * Returns the pid of worker, if everything went ok
 *         -1, if an error ocurred
 */
int launch_worker(worker_t* worker, const matrix* mat1, const matrix* mat2,
			char *hostname, int msocket) {
  
	// create worker
	worker->pid = fork();

	if (worker->pid == 0) { // worker: 
#ifdef VERBOSE
		printf ("worker %d running\n",  worker->id);
#endif

		// obtain submatrix assigned to it: see function submat of the matrix module
		matrix* submat1 = submat(mat1, worker->range);
		// compute the matrix multiplication: see funtion mat_mult of the matrix module
		matrix* result = mat_mul(submat1, mat2);

		// TODO: establishes a reliable/TCP connection to the master
		int worker_socket = myConnectSocket(hostname,msocket ); //msocket e a porta
		assert(worker_socket > -1);
#ifdef VERBOSE
		printf ("Worker_id %d : msocket %d  worker_socket %d \n", 
				worker->id, msocket, worker_socket);
#endif
		// TODO: sends the worker id to the master

		myWriteSocket(worker_socket, (char *)&worker->id, sizeof(unsigned));

		// sends result to the master: see function write_mat
		write_mat(worker_socket, result);

#ifdef VERBOSE
		print_mat(submat1);
		print_mat(result);
		printf ("worker %d done\n",  worker->id);
#endif

		// TODO: closes the TCP communication channel to the master		
		myCloseSocket(worker_socket);

		// the worker terminates
		exit(0);
    }
 
	// master: send pid of the worker or error
	return worker->pid;
}

int par_matmul(const matrix* mat1, const matrix* mat2, worker_t workers[], 
			const unsigned nworkers, char * hostname, int mtcp_port) {

	printf ("Master launching %d workers\n",  nworkers);
   
	const unsigned rows_per_worker = mat1->nrows/nworkers;
	for (unsigned i = 0; i < nworkers; i++) {
		workers[i].id = i;
		workers[i].range[0] = i * rows_per_worker;
		workers[i].range[1] = workers[i].range[0] + rows_per_worker;

		if ((workers[i].pid = launch_worker(&workers[i], mat1, mat2, hostname, mtcp_port)) < 0) 
			return workers[i].pid;
	}

    return 0;

}


void get_result_matrix(matrix* result, worker_t workers[], 
				const unsigned nworkers, int msocket) {
    // receive all results
    for (unsigned i = 0; i < nworkers; i++) {
		// TODO: wait for a connection from a worker
		int sc = myAcceptServerSocket(msocket);
#ifdef VERBOSE
		printf("Connection established to worker socket:%d\n", sc);
#endif
				
		// read the worker's identifier
		unsigned worker_id;
		int nbytes;
		if( (nbytes = myReadSocket( sc, (char *)&worker_id, sizeof(unsigned))) > 0 ) {

			read_mat_into(sc, result, workers[worker_id].range[0]);
#ifdef VERBOSE
			printf ("Master received result from worker %d\n",  workers[worker_id].id);
#endif
			
			wait(NULL);  // waitpid(workers[worker_id].pid, &status, 0);
		}
		else  
			printf("Unable to receive the worker's id %d\n", worker_id);
		
		// TODO: closes the connection to the worker		
		myCloseSocket(sc); 
    }
}



