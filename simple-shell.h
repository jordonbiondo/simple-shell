/**
 * Input buffer
 */
#define INPUT_BUFFER_SIZE 1024

/**
 * User input
 */
char* input_buffer;


/**
 * Tokenized input
 */
char** input_tokens;


/**
 * Read input from stdin and return a pointer to it.
 */
char* read_input(void);

/**
 * Act accordingly to the given input
 */
void handle_input(void);

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


