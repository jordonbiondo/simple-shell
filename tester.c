#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define foobar 3
int main(int argc, char* argv[], char *envp[]) {
  
  if (argc < 2) {
    printf("Usage: must supply a command\n");
    exit(1);
  }
  
  pid_t child_pid = fork();
  int status;
  if(child_pid) {
    waitpid(child_pid, &status, 0);
    printf("child done! status: %d\n", WEXITSTATUS(status));
  } else {
    printf("child running!\n");
    execve(argv[1], &argv[1], envp);
    printf("%s\n", strerror(errno));
    exit(errno);
  }
  
}
