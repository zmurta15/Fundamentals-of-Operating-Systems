#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sched.h>
#include <pthread.h>

void * xxx1(void *t){
  int i; 
  long elapsed;
  struct timeval t1,t2;
  int ntimes = (int)(long)t;
  gettimeofday(&t1, NULL);
  for(i=0; i< ntimes; i++){
    if(fork() != 0) {
      if(fork() != 0) {
        //pai espera pelos dois filhos
        wait(NULL);
        wait(NULL);
      }
      else { //filho2
        gettimeofday(&t1, NULL);
        for(i = 0; i<ntimes; i++) {
          sched_yield();
        }
      }
       gettimeofday(&t2, NULL);
      elapsed = ((long)t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec);
      printf ("Elapsed time = %6li us (%g us/call)\n", elapsed, (double)elapsed/(2*ntimes));
      return NULL;  
      else {
        for(i= 0; i<ntimes; i++)
          sched_yield;
      }
      return NULL;
    }
      
    
	 // sched_yield();
  }
  
}

void * xxx2(void * t){
  int i; 
  int ntimes = (int)(long)t;
  for(i=0; i< ntimes; i++){
	sched_yield();
  }
  return NULL;
}
int main(){
	pthread_t p1, p2;
	pthread_create(&p1,NULL, xxx1, (void *)100000);
	pthread_create(&p2,NULL, xxx2, (void *)100000);

	pthread_join( p1, NULL);	
	pthread_join( p2, NULL);	
	return 0;
}

