#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int pid;

  pid=fork();
  if (!pid) {
    printf("Sou o processo filho, PID:%d\n", getpid() );
    printf("vou tentar listar os ficheiros existentes na directoria\n");
    execl("/bin/ls", "ls", "-l", NULL);
    printf("Se esta mensagem aparece, e' porque o execl falhou \n");
  } else {
      printf("Sou o processo pai, PID:%d\n", getpid());
      wait(NULL);
  }

  return 0;
}

