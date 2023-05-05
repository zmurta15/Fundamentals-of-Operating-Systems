#include <stdio.h>
#include <stdlib.h>

const char strC[]= "Memory map of a (Linux) process\n\n";

char strV[]= "Memory map of a (Linux) process\n\n";

int globalVar;
int globalVarInit= 1;

int main(int argc, char *argv[]) {

  printf("%s%s", strC, strV);

  printf("location of the code      (main):  %p (hex)  %u (dec)\n", main, (unsigned int)main);

  printf("location of a (string) constant :  %p (hex)  %u (dec)\n", strC, (unsigned int)strC);

  printf("location of a (string) variable :  %p (hex)  %u (dec)\n", strV, (unsigned int)strV);

  printf("loc. of a global initialized var:  %p (hex)  %u (dec)\n", &globalVarInit, (unsigned int)&globalVarInit);

  printf("loc. of a global non-init'ed var:  %p (hex)  %u (dec)\n", &globalVar, (unsigned int)&globalVar);

  char *ptr = malloc(100e6);
  printf("location of the top of the heap : %p (hex) %u (dec)\n", ptr, (unsigned int)ptr);

  int x = 3;
  printf("location of the top of the stack: %p (hex) %u (dec)\n", &x, (unsigned int)&x);

  return 0;
}
