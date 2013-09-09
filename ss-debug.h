#include <stdbool.h>

#define DEBUG true

#define LOG_ENTRY if (DEBUG) printf("\tIN  ->%s @ %s:%d\n", __func__, __FILE__, __LINE__)
#define LOG_EXIT  if (DEBUG) printf("\tOUT ->%s @ %s:%d\n", __func__, __FILE__, __LINE__)
#define DEBUG_PRINT if (DEBUG) printf

