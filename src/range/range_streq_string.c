#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#define FLAT_INCLUDES
#include "def.h"
#include "string.h"

bool range_streq_string (const range_const_char * a, const char * b)
{
    range_const_char b_range = { .begin = b, .end = b + strlen (b) };

    return range_streq(a, &b_range);
}
