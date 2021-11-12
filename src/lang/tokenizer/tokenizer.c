#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../table/table.h"
#include "../../table/table-string.h"
#include "../../window/def.h"
#include "../../window/alloc.h"
#include "../../convert/def.h"
#include "tokenizer.h"

static void skip_space (range_const_char * region)
{
    while (region->begin < region->end && isspace(*region->begin))
    {
	region->begin++;
    }
}

static void get_token_size (size_t * size, bool * quote, window_unsigned_char * window)
{
    const char * end = window->region.char_cast.const_cast.begin;
    
    if (!range_is_empty (window->region))
    {
	if (!*quote && (*end == '(' || *end == ')'))
	{
	    *size = 1;
	    return;
	}
	
	while (end < window->region.char_cast.const_cast.end)
	{
	    if (*end == '"')
	    {
		*quote = !*quote;
	    }
	    else if (!*quote)
	    {
		if (isspace (*end) || *end == '(' || *end == ')')
		{
		    break;
		}
	    }
	    
	    end++;
	}
    }
    
    *size = range_index (end, window->region.char_cast.const_cast);
}

bool tokenizer_read (bool * error, window_char * token, window_unsigned_char * buffer, convert_interface * source)
{
    window_alloc (*buffer, 64);

    while (true)
    {
	skip_space (&buffer->region.char_cast.const_cast);

	if (range_is_empty (buffer->region))
	{
	    window_rewrite (*buffer);
	    
	    if (!convert_fill(error, buffer, source))
	    {
		return false;
	    }
	}
	else
	{
	    break;
	}
    }

    assert (!range_is_empty (buffer->region));
    assert (!isspace (*buffer->region.begin));

    size_t size = 0;
    bool quoted = false;
    
    while (true)
    {
	get_token_size (&size, &quoted, buffer);

	assert (size <= (size_t)range_count(buffer->region));

	window_append_bytes((window_unsigned_char*)token, buffer->region.begin, size);
	buffer->region.begin += size;
	
	if (range_is_empty(buffer->region))
	{
	    window_rewrite (*buffer);
	    
	    if (!convert_fill(error, buffer, source))
	    {
		return true;
	    }
	}
	else
	{
	    return true;
	}
    }

    assert (false);
}
