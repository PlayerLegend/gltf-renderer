#ifndef FLAT_INCLUDES
#include <stddef.h>
#define FLAT_INCLUDES
#include "../array/range.h"
#include "def.h"
#endif

long int window_printf(window_char * window, const char * str, ...);
long int window_printf_append(window_char * window, const char * str, ...);
