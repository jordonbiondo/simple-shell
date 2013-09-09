#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "ss-strings.h"
#include "ss-debug.h"

/**
 * Simple Shell
 * main.c
 */

/**
 * Input buffer
 */
#define INPUT_BUFFER_SIZE 1024

/**
 * Function Prototypes
 */
char* read_input(void);

void handle_input(void);

void exit_shell(void);

void tokenize_input(void);

char** tokenize(const char*);

void child_execute_input(char**);

void handle_exit_status(int);

void free_input_tokens(void);

/**
 * Globals
 */
// user input
char* input_buffer;

// tokenized input
char** input_tokens;


/**
 * Main
 */
int main(int argc, char* argv[], char* envp[]) {
  LOG_ENTRY;
  input_buffer = calloc(INPUT_BUFFER_SIZE, sizeof(char));
  while(1) {
    printf(PROMPT_MSG);
    if(read_input() != NULL) {
      handle_input();
      pid_t child_pid = fork();
      int status;
      if(child_pid) { //parent-execution
	waitpid(child_pid, &status, 0);
	DEBUG_PRINT("---------- end ----------------------------------------------------\n");
	handle_exit_status(status);
      } else { //child execution
	child_execute_input(envp);
      }
    } else {
      printf(EOF_ERROR_MSG);
    }
    DEBUG_PRINT("User entered: [%s]\n", input_buffer);
  }
  return 0;
}


/**
 * Execute input
 */
void child_execute_input(char** envp) {
  LOG_ENTRY;
  DEBUG_PRINT("------ child output -----------------------------------------------\n");
  execve(input_tokens[0], input_tokens, envp);
  // if failure
  printf("Failed to execute: %s -> %s\n", input_buffer, strerror(errno));
  LOG_EXIT;
  exit(errno);
}


/**
 * Handle exit status
 */
void handle_exit_status(int status) {
  LOG_ENTRY;
  if (WEXITSTATUS(status)) {
    printf("%s %d\n", CHILD_STATUS_ERROR_MSG, WEXITSTATUS(status));
  }
  LOG_EXIT;
}


/**
 * Handle Input
 */
void handle_input(void) {
  LOG_ENTRY;
  if (strcmp(input_buffer, SHELL_QUIT_CMD) == 0) {
    exit_shell();
  } else {
    input_tokens = tokenize(input_buffer);
  }
  LOG_EXIT;
}


/**
 * Read Input
 */
char* read_input(void) {
  return (char*)fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
}


/**
 * Exit the shell
 */
void exit_shell(void) {
  printf(EXIT_MSG);
  free(input_buffer);
  free_input_tokens();
  exit(0);
}


/**
 * Free Input Tokens.
 */
void free_input_tokens(void) {
  LOG_ENTRY;
  #if DEBUG
  int free_count = 0;
  #endif
  if (input_tokens && *input_tokens) {
    char** foo;
    for (foo = input_tokens; foo && *foo; foo++) {
      #if DEBUG
      free_count++;
      #endif
      free(*foo);
    }
    #if DEBUG
    printf("%d tokens freed\n", free_count);
    #endif
    free(input_tokens);
  }
  LOG_EXIT;
}


/**
 * Tokenize, 
 * Heavily inspired by: http://stackoverflow.com/questions/8106765/using-strtok-in-c
 */
char** tokenize(const char* input) {
  LOG_ENTRY;
  free_input_tokens();
  char* str = strdup(input);
  int tok_count = 0;
  char* tok=strtok(str," \n"); 
  tok_count++;
  while (tok) {
    tok_count++;
    tok = strtok(NULL, " \n");
  }
  free(str);
  char** tokens;
  if (tok_count) {
    str = strdup(input);
    tokens = malloc(tok_count*sizeof(*tokens));
    tok=strtok(str," \n"); 
    int i = 0;
    for (i = 0; i < tok_count; i++) {

      tokens[i] = tok ? strdup(tok) : tok;
      tok=strtok(NULL," \n");
    } 
    
    free(str);
  }
  LOG_EXIT;
  return tokens;
}

