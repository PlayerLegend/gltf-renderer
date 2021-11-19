#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "def.h"
#include "printf.h"
#include "alloc.h"
#include "vprintf.h"

long int window_printf(window_char * window, const char * str, ...)
{
    va_list list;
    va_start(list, str);
    size_t len = window_vprintf (window, str, list);
    va_end(list);
    
    return len;
}
