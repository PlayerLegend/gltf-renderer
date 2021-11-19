#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <string.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "def.h"
#include "alloc.h"
#endif

inline static void window_strcat (window_char * dest, const char * str)
{
    window_append_bytes ( (window_unsigned_char*) dest, (const unsigned char*)str, strlen (str));
}

inline static void window_strcat_range (window_char * dest, range_const_char * src)
{
    window_append_bytes ( (window_unsigned_char*) dest, (const unsigned char*) src->begin, range_count (*src));
}
