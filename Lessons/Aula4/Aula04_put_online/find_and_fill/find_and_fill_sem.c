#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>


//#define SIZE 256*1024*1024
#define SIZE 20
int *array;
int length, count;

pthread_t *ids;
int length_per_thread;
//Define the necessary semaphores
sem_t exmut;
sem_t exmutBarrier;
sem_t fillBarrier;
int maximum = INT_MIN;
int numThreads; 			// Number of total workers 
blockedThreads = 0;		// NUmber of workers blocked in the barrier

void print_vector(int vec[], int length)
{
	for(int i = 0; i < length; i++)
		printf("vec[%d]=%d ", i, vec[i]);
	printf("\n");
}

// Implement a barrier using only semphores
void barrier() {
	sem_wait(&exmutBarrier);
	if (blockedThreads == (numThreads-1)) {
		for (int i =0; i< (numThreads-1); i++) {
			printf("sem post\n");
			sem_post(&fillBarrier);
		}
		blockedThreads = 0;
		sem_post(&exmutBarrier);
	}
	else {
		blockedThreads++;
		sem_post(&exmutBarrier);
		printf("sem_wait\n"); fflush(stdout);
		sem_wait(&fillBarrier);
	}
}

void * find_and_fill(void *id){
	int i, local_max;
	int start =  length_per_thread*(int)(long)id;
	int end = start + length_per_thread;
#ifdef VERBOSE
	printf("i = %d, start = %d, end= %d\n", (int)id, start, end);	
#endif
	// process the partial vector
	local_max = array[start];
		for( i = start; i< end; i++) {
			if(array[i] > local_max) {
				local_max = array[i];
			}
		}

#ifdef VERBOSE
	printf("local_max:%d\n", local_max);
#endif

	// update the global maximum
	sem_wait(&exmut);
	if(local_max> maximum) maximum = loacl_max;
	sem_post(&exmut);

	// Synchronize with the other threads
	barrier();

	// fill the partial vector with the maximum value
	for(i=start; i < end; i++)	
		array[i] = maximum;	

	return NULL;
}

void find_and_fill_parallel(int nthreads){
	int i;	

	// Initialize the necessary semaphores
	sem_init(&exmut, 0, 1);
	sem_init(&exmutBarrier, 0, 1);
	sem_init(&fillBarrier, 0, 0);

	// Launch the threads/workers
	for (i = 0; i < nthreads; i++){
		pthread_create(&ids[i], NULL, find_and_fill, (void*)(long)i);
	}

	// Wait for all threads to terminate
	for (i = 0; i < nthreads; i++){ 
		pthread_join(ids[i], NULL);
	}
}

int main( int argc, char *argv[]){
	int i;

	if( argc < 2 ) {
		printf("Usage: %s num_threads <length_vec>\n", argv[0]);
		return 1;
	} else if(argc == 3)
			length = atoi(argv[2]);
	else 
		length = SIZE;
	int n = atoi(argv[1]);
	if( (length % n) != 0 ) {
		printf("Usage: vector's size must be multiple of the number of threads\n");
		return 1;
	}
	ids = (pthread_t *)malloc(n*sizeof(pthread_t));

	length_per_thread = length / n;
	printf("Using vec length=%d, %d threads; length_per_thread =  %d\n", length, n, length_per_thread);
	
	array= (int *)malloc(length*sizeof(int));

	srand(getpid());
	//srand(0);
	for(i=0; i < length; i++){
		array[i] = rand()%100;
	}
	#ifdef VERBOSE
	print_vector(array, length);
	#endif

	numThreads = n;
	
	find_and_fill_parallel(n);

	#ifdef VERBOSE
	print_vector(array, length);
	#endif


	return 0;
}


