#include <stdbool.h>
#include "ss-debug.h"

/**
 * Input Buffe Size
 */
#define INPUT_BUFFER_SIZE 1024


/**
 * Prompt Buffer Size
 */
#define PROMPT_BUFFER_SIZE 512

#ifdef __CLANG__
#define COMPILER_INLINE static inline
#elseifdef __GNUC__
#define COMPILER_INLINE inline
#endif


/**
 * User input
 */
char* input_buffer;


/**
 * Prompt Buffer
 */
char* prompt_buffer;


/**
 * Tokenized input
 */
char** input_tokens;

/**
 * Display child time
 */
bool display_child_time;


/**
 * Parse args
 */
void parse_args(int, char**);


/**
 * Return the shell prompt
 */
char* get_prompt(void);


/**
 * Dump buffers to stdout
 */
#if DEBUG
void dump_buffers(void);
#endif


/**
 * Display Prompt
 */
void display_prompt(void);


/**
 * Read input from stdin and return a pointer to it.
 */
char* read_input(void);


/**
 * Act accordingly to the given input
 */
bool handle_input(void);


/**
 * Is cd command?
 */
inline bool is_cd_command(char*);


/**
 * Change Directory (cd)
 */
bool change_directory(void);


/**
 * Returns true if a string is all whitespace characters
 */
bool str_is_whitespace(char*);


/**
 * is quit/exit command?
 */
inline bool is_quit_command(char*);


/**
 * Free resources and exit the program
 */
void exit_shell(void);


/**
 * Tokenize the input buffer and write the values to the input tokens.
 */
char** tokenize(const char*);


/**
 * Execute the command tokens in the child process
 */
void child_execute_input(char**);


/**
 * Act accordingly to the child's exit status
 */
void handle_exit_status(int);


/**
 * Free all token resources
 */
void free_input_tokens(void);
