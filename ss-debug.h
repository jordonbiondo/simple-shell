#include <stdbool.h>

/**
 * Debug flag
 */
#ifndef DEBUG
  #define DEBUG 0  
#endif
#define LOG_ENTRY if (DEBUG) printf("\tIN  ->%s @ %s:%d\n", __func__, __FILE__, __LINE__)

#define LOG_EXIT  if (DEBUG) printf("\tOUT ->%s @ %s:%d\n", __func__, __FILE__, __LINE__)

#define DEBUG_PRINT if (DEBUG) printf

