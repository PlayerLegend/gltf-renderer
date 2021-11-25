#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "def.h"

#include "../log/log.h"

convert_interface * convert_interface_new (size_t arg_size)
{
    return calloc (1, sizeof(convert_interface));
}

bool convert_fill (bool * error, window_unsigned_char * output, convert_interface * interface)
{
    unsigned char * start = output->region.end;

    while ( output->region.end < output->alloc.end && convert_read(error, output, interface, -1) )
    {}
    
    return !*error && output->region.end != start;
}

bool convert_fill_limit (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit)
{
    window_alloc (*output, limit);
    
    while ( (size_t)range_count (output->region) < limit && convert_read(error, output, interface, limit) )
    {}

    if (range_is_empty (output->region))
    {
	return false;
    }

    if ((size_t)range_count (output->region) < limit)
    {
	*error = true;
	return false;
    }

    assert ((size_t)range_count (output->region) >= limit);
    
    return !*error && (size_t)range_count (output->region) >= limit;
}

bool convert_drain (bool * error, window_unsigned_char * output, convert_interface * interface)
{
    unsigned char * start = output->region.begin;

    while ( output->region.begin < output->region.end && convert_write(error, output, interface, -1) )
    {}
    
    return !*error && (output->region.begin != start || range_is_empty (output->region));
}

bool convert_load_all (bool * error, window_unsigned_char * output, convert_interface * interface)
{
    window_unsigned_char tmp = {0};

    window_alloc (tmp, 65535);

    while (convert_fill (error, &tmp, interface))
    {
	window_append_bytes (output, tmp.region.begin, range_count(tmp.region));
	window_rewrite (tmp);
    }

    free (tmp.alloc.begin);

    *window_push (*output) = '\0';
    output->region.end--;

    return !*error;
}

void convert_free(convert_interface * interface)
{
    interface->clear(interface);
    free (interface);
}
