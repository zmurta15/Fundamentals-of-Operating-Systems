#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>
 #include <sys/types.h>
 #include <unistd.h>


//#define SIZE 256*1024*1024
#define SIZE 20
int *array;
int length, count;

pthread_t *ids;
int length_per_thread;
pthread_mutex_t ex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t fillBarrier;
int maximum = INT_MIN;

void print_vector(int vec[], int length)
{
	for(int i = 0; i < length; i++)
		printf("vec[%d]=%d ", i, vec[i]);
	printf("\n");
}

// Code executed by each thread
void * find_and_fill(void *id){
	int i;
	int local_max;
	int start =  length_per_thread*(int)(long)id;
	int end = start + length_per_thread;
#ifdef VERBOSE
	printf("id = %d, start = %d, end= %d\n", (int)id, start, end);	
#endif
	// process the partial vector
	for( i = start; i< end; i++) {
		if(array[i] > local_max) {
			local_max = array[i];
		}
	}

#ifdef VERBOSE
	printf("local_max:%d\n", local_max);
#endif

	// update the global maximum
	pthread_mutex_lock(&ex);
	if (local_max > maximum) {
		maximum = local_max;
	}
	pthread_mutex_unlock(&ex);

	// pthreads barrier
	pthread_barrier_wait (&fillBarrier);

	// fill the partial vector with the maximum value
	for(i=start; i < end; i++)	
		array[i] = maximum;	

	return NULL;
}

// Code with the creation of multiple threads
void find_and_fill_parallel(int nthreads){
	int i;
	pthread_barrier_init(&fillBarrier, NULL,  nthreads);
	for (i = 0; i < nthreads; i++){
		pthread_create(&ids[i], NULL, find_and_fill, (void*)(long)i);
	}
	for (i = 0; i < nthreads; i++){ //precisa para o pai esperar pelos filhos
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

	find_and_fill_parallel(n);

	#ifdef VERBOSE
	print_vector(array, length);
	#endif


	return 0;
}


