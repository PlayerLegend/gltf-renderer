#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "def.h"
#include "vprintf.h"
#include "alloc.h"

long int window_vprintf(window_char * window, const char * format, va_list ap)
{
    va_list copy;
    va_copy(copy, ap);
    size_t len = vsnprintf(NULL, 0, format, copy);
    va_end(copy);

    size_t new_size = len + 1;

    window_rewrite (*window);
    window_alloc(*window, new_size); 

    va_copy(copy, ap);
    vsprintf(window->region.begin, format, copy);
    va_end(copy);

    window->region.end = window->region.begin + len;
    *window->region.end = '\0';

    return len;
}
