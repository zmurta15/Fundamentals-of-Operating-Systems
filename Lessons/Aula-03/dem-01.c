#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {

  printf("Aquilo que estou a escrever neste momento vai aparecer no ecra\n" );

  close(1);
  open("dem-01.txt", O_WRONLY|O_CREAT, 0660);
 
  printf("Aquilo que estou a escrever agora vai aparecer no ficheiro dem-01.txt\n" );

  return 0;
}
