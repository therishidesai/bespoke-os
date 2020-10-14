#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char *argv) {
  int p[2];
  pipe(p);

  int pid = fork();
  if (pid == 0) {
    // child process
    char data[1];
    read(p[0], data, 1);
    printf("%d: received ping\n", getpid());
    close(p[0]);
    write(p[1], data, 1);
    close(p[1]);
  } else if (pid > 0) {
    // parent process
    char data[1];
    write(p[1], "a", 1);
    close(p[1]);
    wait((int*) 0);
    read(p[0], data, 1);
    printf("%d: received pong\n", getpid());
    close(p[0]);
    exit(0);
  } else {
    fprintf(2, "fork failed!\n");
    exit(1);
  }

  exit(0);
}
