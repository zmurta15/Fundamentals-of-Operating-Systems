#include <stdio.h>
#include <stdlib.h>

const char strC[]= "Memory map of a (Linux) process\n\n";

char strV[]= "Memory map of a (Linux) process\n\n";

int globalVar;
int globalVarInit= 1;

int main(int argc, char *argv[]) {

  strV[0] = 'C';
  //strC[0] = 'X';
  printf("nova sring strV:%s\n\n", strV);
  //printf("nova string strC:%s\n\n", strC);

  char *ptrStr;
  ptrStr = strC;
  *ptrStr = 'k';
  printf("nova cadeia strC:%s\n\n", strC);

  printf("%s%s", strC, strV);

  printf("location of the code      (main):  %p (hex)  %llu (dec)\n", main, (unsigned long long int)main);

   printf("location of a (string) constant :  %p (hex)  %llu (dec)\n", strC, (unsigned long long int)strC);

  printf("location of a (string) variable :  %p (hex)  %llu (dec)\n", strV, (unsigned long long int)strV);

  printf("loc. of a global initialized var:  %p (hex)  %llu (dec)\n", &globalVarInit, (unsigned long long int)&globalVarInit);

  printf("loc. of a global non-init'ed var:  %p (hex)  %llu (dec)\n", &globalVar, (unsigned long long int)&globalVar);

  char *ptr = malloc(100e6);
  printf("location of the top of the heap : %p (hex) %llu (dec)\n", ptr, (unsigned long long int)ptr);

 char *pty = malloc(100e6);
  printf("location of the top of the heap : %p (hex) %llu (dec)\n", pty, (unsigned long long int)pty);

  int x = 3;
  printf("location of the top of the stack: %p (hex) %llu (dec)\n", &x, (unsigned long long int)&x);

  int y = 4;
  printf("location of the top of the stack: %p (hex) %llu (dec)\n", &y, (unsigned long long int)&y);
	
  return 0;
}
