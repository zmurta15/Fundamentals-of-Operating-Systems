#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

#define SIZE 1*1024*1024
int *array;
int length, count;

pthread_t *ids;
int length_per_thread;
pthread_mutex_t ex = PTHREAD_MUTEX_INITIALIZER;

// Code executed by each thread
void * count3s_thread(void *id){
	int i, c = 0;
	int start = length_per_thread*(int)(long)id;
	int end = start + length_per_thread;
#ifdef VERBOSE
	printf("i = %d, start = %d, end = %d\n", (int)id, start, end);
#endif
	for ( i = start; i < end;  i++) {
		if(array[i] == 3) {
			c++;
		}
	}
	pthread_mutex_lock(&ex);
	count += c;
	pthread_mutex_unlock(&ex);
	return NULL;
}

// Code with the creation of multiple threads
void count3s(int nthreads){
	int i;
	for ( i = 0; i < nthreads; i++){
		pthread_create(&ids[i], NULL, count3s_thread, (void *)(long)i);
	}
	for ( i = 0; i < nthreads; i++){
		pthread_mutex_lock(&ex);
		pthread_join(ids[i], NULL);
	}
}

int main( int argc, char *argv[]){
	int i;

	if( argc != 2 ) {
		printf("Usage: %s num_threads\n", argv[0]);
		return 1;
	}
	int n = atoi(argv[1]);
	if( (SIZE % n) != 0 ) {
		printf("Usage: vector's size must be multiple of the number of threads\n");
		return 1;
	}
	ids = (pthread_t *)malloc(n*sizeof(pthread_t));

	length_per_thread = SIZE / n;
	printf("Using %d threads; length_per_thread =  %d\n", n, length_per_thread);
	
	array= (int *)malloc(SIZE*sizeof(int));
	length = SIZE;
	// srand(getpid());
	srand(0);
	for(i=0; i < length; i++){
		array[i] = rand() % 4;
	}

	count3s(n);

	printf("Count of 3s = %d\n", count);

	return 0;
}


