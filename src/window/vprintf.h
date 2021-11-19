#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdarg.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "def.h"
#endif

long int window_vprintf(window_char * window, const char * format, va_list ap);
long int window_vprintf_append(window_char * window, const char * format, va_list ap);
