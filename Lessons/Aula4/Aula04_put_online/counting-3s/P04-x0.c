#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define SIZE 256*1024*1024
int *array;
int length, count;

int count3s(){
	int i;
	count = 0;
	
	for(i=0; i < length; i++){
		if(array[i] == 3){
			count++;
		}
	}
	return count;
}

int main( int argc, char *argv[]){
	int i, r;

	array= (int *)malloc(SIZE*sizeof(int));
	length = SIZE;
//	srand(getpid());
	srand(0);
	for(i=0; i < length; i++){
		array[i] = rand() % 4;
	}
	r = count3s();
	printf("Count of 3s = %d\n", r);
	return 0;
}


