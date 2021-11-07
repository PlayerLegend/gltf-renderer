#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "def.h"
#include "alloc.h"

void _window_alloc (window_void * window, size_t member_size, size_t new_count)
{
    size_t available_size = (char*) window->alloc.end - (char*) window->region.begin;

    if (available_size >= new_count * member_size)
    {
	return;
    }

    size_t alloc_size = (char*) window->alloc.end - (char*) window->alloc.begin;

    size_t released_size = (char*) window->region.begin - (char*) window->alloc.begin;

    size_t region_size = (char*) window->region.end - (char*) window->region.begin;
	
    if (released_size > alloc_size / 2) // trim the beginning
    {
	size_t want_alloc_size = 2 * new_count * member_size;

	if (want_alloc_size <= alloc_size) // memmove
	{
	    memmove (window->alloc.begin, window->region.begin, region_size);
	    window->region.begin = window->alloc.begin;
	    window->region.end = (char*) window->region.begin + region_size;
	}
	else // malloc, memcpy, free
	{
	    alloc_size = want_alloc_size;
	    char * new_alloc = malloc(alloc_size);
	    if (!new_alloc)
	    {
		perror ("malloc");
		exit (1);
	    }
	    memcpy (new_alloc, window->region.begin, region_size);
	    free (window->alloc.begin);
	    window->alloc.begin = new_alloc;
	    window->alloc.end = new_alloc + alloc_size;
	    window->region.begin = new_alloc;
	    window->region.end = new_alloc + region_size;
	}
    }
    else // realloc
    {
	alloc_size = 2 * (released_size + new_count * member_size);

	char * new_alloc = realloc (window->alloc.begin, alloc_size);

	if (!new_alloc)
	{
	    perror ("realloc");
	    exit (1);
	}

	window->alloc.begin = new_alloc;
	window->alloc.end = new_alloc + alloc_size;
	window->region.begin = new_alloc + released_size;
	window->region.end = new_alloc + released_size + region_size;
    }

    assert ( ( (char*) window->region.end - (char*) window->region.begin ) % member_size == 0 ); // region size
    assert ( ( (char*) window->region.begin - (char*) window->alloc.begin ) % member_size == 0 ); // released
    assert ( ( (char*) window->alloc.end - (char*) window->alloc.begin ) % member_size == 0 ); // alloc
    
    assert (window->region.begin <= window->region.end);
    assert (window->alloc.begin <= window->region.begin);
    assert (window->region.end <= window->alloc.end);
}

void window_append_bytes (window_unsigned_char * window, const unsigned char * begin, size_t size)
{
    window_alloc (*window, range_count(window->region) + size);
    memcpy (window->region.end, begin, size);
    window->region.end += size;
}

void _window_clear (window_void * window)
{
    free (window->alloc.begin);
    window->alloc.begin
	= window->alloc.end
	= window->region.begin
	= window->region.end
	= NULL;
}
