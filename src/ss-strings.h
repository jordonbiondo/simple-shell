
/**
 * ss-strings.h
 */

/**
 * Error
 */
#define EOF_ERROR_MSG "\n\x1b[31mError:\x1b[0m EOF encountered in command!\n"

/**
 * Prompt
 */
#define PROMPT_MSG "Enter command: "

/**
 * Exit
 */
#define EXIT_MSG "Exitting...\n"

/**
 * Child Error
 */
#define CHILD_STATUS_ERROR_MSG "Child process exited with a status of"


/**
 * Exec time
 */
#define CHILD_EXECUTION_TIME_FMT "Child used \x1b[32m%f \x1b[0mseconds of precious processing time.\n"

/**
 * Exec failed
 */
#define FAILED_TO_EXEC_FMT "\x1b[31mFailed to execute: \x1b[0m%s -> \x1b[33m%s\x1b[0m\n"

/**
 * Change Dir Failed
 */
#define CHANGE_DIR_ERROR_MSG "\x1b[31mFailed\x1b[0m"
