#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define NTRIES  1000
#define PAGESIZE 4096


//int do_something(void) { return 1; }
int n;

int main (int argc, char *argv[]) {
   // int i, p;
    long elapsed;
    struct timeval t1,t2;

        scanf("%d", &n);
        char *v = malloc(PAGESIZE*n);
        gettimeofday(&t1, NULL);
        for(int j = 0; j<(n*PAGESIZE); j += PAGESIZE) {
          char a =  v[j];
        }
        gettimeofday(&t2, NULL);
        elapsed = ((long)t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec);
        printf ("Elapsed time = %6li us (%g us/call)\n", elapsed, (double)elapsed/NTRIES);
        
    return 0;
}

