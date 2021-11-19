#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"

bool resolve_path (window_char * output, const char * cwd, window_char * input)
{
    range_typedef(range_const_char, range_const_char);
    window_typedef(range_const_char, range_const_char);

    range_const_char range = { .begin = input->region.begin };

    window_range_const_char stack = {0};

    while (true)
    {
	while (*range.begin == '/')
	{
	    range.begin++;
	}

	range.end = range.begin + 1;
	
	while (range.end < input->region.end && *range.end != '/')
	{
	    range.end++;
	}

	if (range_streq_string(&range, ".."))
	{
	    if (range_is_empty (stack.region))
	    {
		log_fatal ("Requested path is outside of chroot: %s", input->region.begin);
	    }
	    else
	    {
		stack.region.end--;
		continue;
	    }
	}
	else
	{
	    *window_push(stack) = range;
	}
    }

    range_const_char * range_p;

    window_printf (output, "");

    for_range (range_p, stack.region)
    {
	window_printf_append (output, "/%.*s", range_count(*range_p), range_p->begin);
    }

    free (stack.alloc.begin);
    return true;
    
fail:
    free (stack.alloc.begin);
    return false;
}
