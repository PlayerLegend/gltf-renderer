#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "def.h"
#include "printf.h"
#include "alloc.h"

long int window_printf_append(window_char * window, const char * str, ...)
{
    va_list list;
    va_start(list, str);
    size_t len = vsnprintf(NULL, 0, str, list);
    va_end(list);

    size_t old_size = range_count(window->region);

    size_t new_size = old_size + len + 1;

    window_alloc(*window, new_size); 

    va_start(list, str);
    vsprintf(window->region.end, str, list);
    va_end(list);

    window->region.end += len;
    *window->region.end = '\0';

    return len;
}
