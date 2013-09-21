
/**
 * This is a messy place...
 */

/**
 * Debug flag
 */
#ifndef _SS_DEBUG_H_
#ifndef DEBUG
  #define DEBUG 0
#endif

/**
 * Colors
 */
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"


/**
 * Function begin
 */
#define LOG_ENTRY							\
  if (DEBUG) printf("\t%sIN%s  -> %s @ %s:%d\n",			\
		    COLOR_GREEN, COLOR_RESET ,__func__, __FILE__, __LINE__)


/**
 * System exit
 */
#define LOG_EXIT(x)							\
  if (DEBUG) printf("\t%sOUT%s -> %s @ %s:%d\n",			\
		    COLOR_YELLOW, COLOR_RESET, __func__, __FILE__, __LINE__); exit(x)

/**
 * Printf if debug
 */
#define DEBUG_PRINT if (DEBUG) printf


/**
 * Beginning of child output
 */
#define CHILD_OUT_START							\
  DEBUG_PRINT("%s------ child output -----------------------------------------------\n%s", \
	      COLOR_BLUE, COLOR_RESET)

/**
 * End of child output
 */
#define CHILD_OUT_END							\
  DEBUG_PRINT("%s---------- end ----------------------------------------------------\n%s", \
	      COLOR_BLUE, COLOR_RESET)


#if DEBUG
/**
 * Function return with debug
 */
#define LOG_RETURN(x) printf("\t%sOUT%s -> %s @ %s:%d\n",		\
			     COLOR_YELLOW, COLOR_RESET, __func__, __FILE__, __LINE__); return x;
#else
/**
 * Function return
 */
#define LOG_RETURN(x) return x;
#endif
#endif
