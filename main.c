#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


/* #include "ss-tokens.h" */
#include "ss-strings.h"
#include "ss-debug.h"

#define INPUT_BUFFER_SIZE 1024


/**
 * Prototypes
 */
char* read_input(void);
void prompt_user(void);
void handle_input(void);
void exit_shell(void);
void tokenize_input(void);
char** tokenize(const char*);

/**
 * Globals
 */
char* input_buffer;

char** input_tokens;


/**
 * Main
 */
int main(int argc, char* argv[], char* envp[]) {
  LOG_ENTRY;
  input_buffer = calloc(INPUT_BUFFER_SIZE, sizeof(char));
  while(1) {
    prompt_user();
    if(read_input() != NULL) {
      handle_input();
      pid_t child_pid = fork();
      int status;
      if(child_pid) {
	waitpid(child_pid, &status, 0);
	if (WEXITSTATUS(status)) {
	  printf("Exited with a status of %d\n", WEXITSTATUS(status));
	}
      } else {
	printf("Executing: %s\n", input_tokens[0]);
	execve(input_tokens[0], &input_tokens[0], envp);
	printf("%s\n", strerror(errno));
	exit(errno);
      }
      
    } else {
      printf(ERROR_MSG);
    }
    if (DEBUG) printf("User entered: %s\n", (char*)&input_buffer);
  }
  return 0;
}


/**
 * Prompt User
 */
void prompt_user(void) {
  printf(PROMPT_MSG);
}

/**
 * Handle Input
 */
void handle_input(void) {
  printf("handlining input\n");
  if (strcmp(input_buffer, SHELL_QUIT_CMD) == 0) {
    exit_shell();
  } else {
    input_tokens = tokenize(input_buffer);
  }
}

/**
 * Read Input
 */
char* read_input(void) {
  return (char*)fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
}


/**
 * Tokenize Input

/**
 * Exit the shell
 */
void exit_shell(void) {
  printf(EXIT_MSG);
  exit(0);
}

/**
 * Tokenize, 
 * Temporarily stolen from: http://stackoverflow.com/questions/8106765/using-strtok-in-c
 */
char** tokenize(const char* input) {
  LOG_ENTRY;
  char* str = strdup(input);
  int i = 0;
  int current_count = 10;
  char** tokens = malloc(current_count*sizeof(*tokens));
  
  char* tok=strtok(str," "); 
  
  while(1)
    {
      if (i >= current_count)
	tokens = realloc(tokens, (current_count*=2)*sizeof(*tokens));
      
      tokens[i++] = tok? strdup(tok) : tok;
      
      if (!tok) break;
      
      tok=strtok(NULL," ");
    } 
  
  free(str);
  LOG_EXIT;
  return tokens;
}

