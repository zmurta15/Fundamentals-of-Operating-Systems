#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXC 2048
#define ARGVMAX 50
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {

    char line [MAXC]; //tipo cadeia
    char *args[ARGVMAX];
    int end = FALSE;
     while(!end) {
         printf("mish>");
         fgets(line, MAXC, stdin);
         int nTokens = makeargv(line, args);
         int bg = FALSE;   //bg = background
         if(!strcmp(args[nTokens-1], "&")) {
             bg = TRUE;
             args[--nTokens] = NULL;
         }
         int pid = fork();
         if(pid==0) {     //codigo filho
            execvp(args[0], args);
            perror("Erro execpv");
            exit(0);
         }
         else if(pid>0) { //codigo pai
            if(!bg) {
                wait(NULL);
                //int exist; wait(&exist);
            }
         }
         else {
            perror("erro no fork()");
         }
     }
    return 0;
}


int makeargv(char *s, char *argv[]) {
// in: s points a text string with words
// pre: argv is predefined as char *argv[ARGVMAX]
// out: argv[] points to all words in the string s (*s is modified!)
// return: number of words pointed to by the elements in argv (or -1 in case of error)
    int ntokens;
    if ( s==NULL || argv==NULL || ARGVMAX==0 )
        return -1;
    ntokens = 0;
    argv[ntokens]=strtok(s, " \t\n");
    while ( (argv[ntokens]!= NULL) && (ntokens<ARGVMAX) ) {
        ntokens++;
         argv[ntokens]=strtok(NULL, " \t\n"); // breaks 's' inline at separators
    }
    argv[ntokens] = NULL; // terminate with NULL reference
    return ntokens;
}