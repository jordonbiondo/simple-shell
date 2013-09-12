/* simple-shell.c --- A simple shell  
 * 
 * Filename: simple-shell.c
 * Description: A simple shell
 * Author: Jordon Biondo, Doug MacDonald
 * Created: Mon Sep  9 00:14:19 2013 (-0400)
 * Version: 0.2.4
 * Last-Updated: Thu Sep 12 10:03:27 2013 (-0400)
 *           By: Jordon Biondo
 *     Update #: 25
 * URL: https://github.com/jordonbiondo/simple-shell
 *
 **********************************
 * Commentary: 
 * 
 * Provides a basic shell.
 *
 ***********************************
 * Built in commands:
 * 
 *   quit             : exit the shell
 *   exit             : same is quit
 *   cd [target dir]  : change current directory to target directory
 *  
 **********************************/

/* Code: */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


#include "simple-shell.h"
#include "ss-strings.h"
#include "ss-debug.h"

/**
 * Simple Shell
 * main.c
 */

/**
 * Main
 */
int main(int argc, char* argv[], char* envp[]) {
  LOG_ENTRY;
  parse_args(argc, argv);
  input_buffer = calloc(INPUT_BUFFER_SIZE, sizeof(char));
  prompt_buffer = calloc(PROMPT_BUFFER_SIZE, sizeof(char));
  while(1) {
    display_prompt();
    if(read_input() != NULL) {
      bool valid = handle_input();
      if (valid) {
	pid_t child_pid = fork();
	int status;
	if(child_pid) { //parent-execution
	  struct rusage child_info;
	  wait4(child_pid, &status, 0, &child_info);
	  if (display_child_time) {
	    printf(CHILD_EXECUTION_TIME_FMT, 
		   (float) (child_info.ru_stime.tv_sec + child_info.ru_utime.tv_sec) + 
		   (float) (child_info.ru_stime.tv_usec + child_info.ru_utime.tv_usec) / 1000000);
	  }
	  CHILD_OUT_END;
	  handle_exit_status(status);
	} else { //child execution
	  child_execute_input(envp);  
	}
      }
    } else {
      printf(EOF_ERROR_MSG);
      exit_shell();
    }
    #if DEBUG
    dump_buffers();
    #endif
  }
  LOG_RETURN(0);
}


/**
 * Parse args
 */
void parse_args(int argc, char** argv) {
  display_child_time = true;
  if (argc >= 2 && (strcmp(argv[1], "-notime") == 0)) {
    display_child_time = false;
  }
}


/**
 * Get the prompt string.
 */
char* get_prompt() {
  LOG_ENTRY;
  getcwd(prompt_buffer, PROMPT_BUFFER_SIZE);
  #if DEBUG
    LOG_RETURN(prompt_buffer);
  #else
    LOG_RETURN(strrchr(prompt_buffer, '/') + 1);
  #endif
}


/**
 * Display Prompt
 */
void display_prompt(void) {
  printf("%s[%sSimpSH:%s%s]%s> ", COLOR_BLUE, COLOR_RESET, get_prompt(), COLOR_BLUE, COLOR_RESET);
}


/**
 * Execute input.
 */
void child_execute_input(char** envp) {
  LOG_ENTRY;
  CHILD_OUT_START;
  execvp(input_tokens[0], input_tokens);
  // if failure
  printf(FAILED_TO_EXEC_FMT, input_buffer, strerror(errno));
  LOG_EXIT(errno);
}


/**
 * Handle exit status.
 */
void handle_exit_status(int status) {
  LOG_ENTRY;
  if (WEXITSTATUS(status)) {
    printf("%s %d\n", CHILD_STATUS_ERROR_MSG, WEXITSTATUS(status));
  }
  LOG_RETURN();
}



/**
 * Handle Input.
 */
bool handle_input(void) {
  LOG_ENTRY;
  if (is_quit_command(input_buffer)) {
    exit_shell();
    LOG_RETURN(false);
  } else if (is_cd_command(input_buffer)) {
    change_directory();
    LOG_RETURN(false);
  } else if (str_is_whitespace(input_buffer)) {
    LOG_RETURN(false);
  } else {
    input_tokens = tokenize(input_buffer);
    LOG_RETURN(true);
  }
}


/**
 * Returns true if a string is all whitespace characters.
 */
bool str_is_whitespace(char* str) {
  LOG_ENTRY;
  char* c;
  for (c = str; c && *c; c++) {
    if (!(*c == ' ' || *c == '\t' || *c == '\n')) {
      LOG_RETURN(false);
    }
  }
  LOG_RETURN(true);
}


/**
 * Is cd command?
 */
inline bool is_cd_command(char* buffer) {
  return (strncmp(buffer, "cd", 2) == 0 && buffer[2] == ' ');
}


/**
 * Change Directory. 
 */
bool change_directory(void) {
  LOG_ENTRY;
  int input_length = strlen(input_buffer);

  char target_dir [input_length - 3];
  memcpy(target_dir, input_buffer + 3, input_length - 3);
  target_dir[input_length-3-1] = '\0';

  if(chdir(target_dir)) {
    printf("%s: %s", CHANGE_DIR_ERROR_MSG, strerror(errno));
    LOG_RETURN(false);
  }
  LOG_RETURN(true);
}

/**
 * Read Input.
 */
char* read_input(void) {
  LOG_ENTRY;
  char* x = (char*)fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
  LOG_RETURN(x);
}


/**
 * Is quit/exit command?
 */
inline bool is_quit_command(char* buffer) {
  return (strcmp(buffer, "quit\n") == 0) || (strcmp(buffer, "exit\n") == 0);
}


/**
 * Exit the shell.
 */
void exit_shell(void) {
  LOG_ENTRY;
  printf(EXIT_MSG);
  free(prompt_buffer);
  free(input_buffer);
  free_input_tokens();
  LOG_EXIT(0);
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
  LOG_RETURN();
}


/**
 * Tokenize, 
 * Heavily inspired: http://stackoverflow.com/questions/8106765/using-strtok-in-c
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
  LOG_RETURN(tokens);
}


#if DEBUG
void dump_buffers(void) {
  printf("%s-----------------dumping buffers-------------------------------------%s\n",
	 COLOR_RED, COLOR_RESET);
  printf("  - input_buffer: %s\n", input_buffer);
  printf("  - prompt_buffer: %s\n", prompt_buffer);
  printf("  - tokens:\n");
  char** token_p;
  for (token_p = input_tokens; token_p && *token_p; token_p++) {
    printf("    - tok: %s\n", *token_p);
  }
  printf("%s---------------------end dump----------------------------------------%s\n",
	 COLOR_RED, COLOR_RESET);
}
#endif
