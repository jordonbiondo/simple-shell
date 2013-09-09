#include <stdbool.h>

/**
 * Debug flag
 */
#ifndef DEBUG
  #define DEBUG 0  
#endif
#define LOG_ENTRY if (DEBUG) printf("\tIN  ->%s @ %s:%d\n", __func__, __FILE__, __LINE__)

#define LOG_EXIT(x)  if (DEBUG) printf("\tOUT ->%s @ %s:%d\n", __func__, __FILE__, __LINE__); exit(x)

#define DEBUG_PRINT if (DEBUG) printf

#define CHILD_OUT_START DEBUG_PRINT("------ child output -----------------------------------------------\n")

#define CHILD_OUT_END DEBUG_PRINT("---------- end ----------------------------------------------------\n")


#if DEBUG
#define LOG_RETURN(x) printf("\tOUT ->%s @ %s:%d\n", __func__, __FILE__, __LINE__); return x;
#else
#define LOG_RETURN(x) return x;
#endif

