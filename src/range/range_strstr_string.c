#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "range.h"
#include "string.h"
#include "../libc/string.h"

bool range_strstr_string (const range_const_char * haystack, const char * needle)
{
    range_const_char needle_range = { .begin = needle, .end = needle + strlen (needle) };

    return range_strstr(haystack, &needle_range);
}
