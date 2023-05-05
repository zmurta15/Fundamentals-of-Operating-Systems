#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#define NTRIES  1000


int do_something(void) { return 1; }

int main (int argc, char *argv[]) {
    int i, p;
    pthread_t t;
    long elapsed;
    struct timeval t1,t2;
    gettimeofday(&t1, NULL);
    for (i = 0;  i < NTRIES; i++)
        if(fork() != 0)
            wait(NULL);
        else{
           pthread_create(&t, NULL, func, NULL);
           pthread_join(t, NULL);
         }
             
        gettimeofday(&t2, NULL);
        elapsed = ((long)t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec);
        printf ("Elapsed time = %6li us (%g us/call)\n", elapsed, (double)elapsed/NTRIES);
    }
    return 0;
}

