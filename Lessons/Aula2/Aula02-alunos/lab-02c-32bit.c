#include <stdio.h>
#include <stdlib.h>

unsigned int v2p(unsigned int vaddr);

const char strC[]= "Memory map of a (Linux) process\n\n";

char strV[]= "Memory map of a (Linux) process\n\n";

int globalVar;
int globalVarInit= 1;

int main(int argc, char *argv[]) {

  printf("%s%s", strC, strV);

  printf("                                   virtual      real\n");

  printf("location of the code (main)       %p 0x%x\n", main, v2p( (unsigned int)main ) );
  printf("location of the code (main)       %u %u\n\n", (unsigned int)main, v2p( (unsigned int)main ) );

  printf("location of a (string) constant   %p 0x%x\n", strC, v2p( (unsigned int)strC ) );
  printf("location of a (string) constant   %u %u\n\n", (unsigned int)strC, v2p( (unsigned int)strC ) );

  printf("location of a (string) variable   %p 0x%x\n", strV, v2p( (unsigned int)strV ) );
  printf("location of a (string) variable   %u %u\n\n", (unsigned int)strV, v2p( (unsigned int)strV ) );

  printf("loc. of a global non-init'ed var  %p 0x%x\n", &globalVar, v2p( (unsigned int)&globalVar ) );
  printf("loc. of a global non-init'ed var  %u %u\n\n", (unsigned int)&globalVar, v2p( (unsigned int)&globalVar ) );

  printf("loc. of a global initialized var  %p 0x%x\n", &globalVarInit, v2p( (unsigned int)&globalVarInit ) );
  printf("loc. of a global initialized var  %u %u\n\n", (unsigned int)&globalVarInit, v2p( (unsigned int)&globalVarInit ) );

  char *ptr = malloc(100e6);
  printf("location of the top of the heap  %p 0x%x\n", ptr, v2p( (unsigned int)ptr ) );
  printf("location of the top of the heap  %u %u\n\n", (unsigned int)ptr, v2p( (unsigned int)ptr ) );

  int x = 3;
  printf("location of the top of the stack %p 0x%x\n", &x, v2p( (unsigned int)&x ) );
  printf("location of the top of the stack %u %u\n\n", (unsigned int)&x, v2p( (unsigned int)&x ) );

  return 0;
}
