
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

char c = 'X';

void pipe1(int inp,int out, int ntimes){
  // inp is the channel used to read from the pipe
  // out is the channel used to write into the pipe
  int i; char l;
  long elapsed;
  struct timeval t1,t2;
  gettimeofday(&t1, NULL);
  for(i=0; i< ntimes; i++){
	// code to fill in, that sends ‘X’ to the other process and receives the same byte from it

  }
   gettimeofday(&t2, NULL);
   elapsed = ((long)t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec);
   printf ("Elapsed time = %6li us (%g us/call)\n", elapsed, (double)elapsed/(2*ntimes));
}
void pipe2(int inp, int out, int ntimes){
  // inp is the channel used to read from the pipe
  // out is the channel used to write into the pipe
  int i; char l;
  for(i=0; i< ntimes; i++){
	// code to fill in that receives a byte from the other process and echoes it 

  }
}
int main(){
	int fd1[2];
	int fd2[2];
	pipe(fd1);
	pipe(fd2);
	int p = fork();
	if(p==0){
               // replace ? by the appropriate channels
		pipe2(? , ? , 100000 );
		exit(0);
	}else{
		p = fork();
		if(p==0){
                     // replace ? by the appropriate channels
			pipe1(?, ?, 100000);
			exit(0);
		}
		else{
			wait(NULL);
			wait(NULL);
		}
	}
	return 0;
}

