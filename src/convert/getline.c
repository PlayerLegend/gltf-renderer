#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../range/string.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "def.h"
#include "getline.h"

#include "../log/log.h"

bool convert_getline (bool * error, range_const_char * line, window_unsigned_char * buffer, convert_interface * interface, const range_const_char * end_sequence)
{
    size_t region_size;

    size_t end_point;

    while (!(region_size = range_count(buffer->region)) || region_size == (end_point = range_strstr (&buffer->signed_cast.region.const_cast, end_sequence)))
    {
	window_alloc (*buffer, range_count(buffer->region) + 20);
	if (!convert_read (error, buffer, interface, -1))
	{
	    return false;
	}
    }

    assert (region_size > end_point);

    assert (!*error);
    
    line->begin = buffer->signed_cast.region.const_cast.begin;
    line->end = line->begin + end_point;
    window_release (*buffer, range_count(*line) + range_count (*end_sequence));
    
    return true;
}
