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
#include "fd.h"

#include "../log/log.h"

bool convert_read_fd (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit)
{
    convert_interface_fd * io = (convert_interface_fd*) interface;
    
    size_t max = output->alloc.end - output->region.begin;

    if (max > limit)
    {
	max = limit;
    }

    assert (output->region.end <= output->alloc.end);
    assert (output->region.end >= output->region.begin);

    size_t remaining = max - range_count (output->region);
    
    if (!remaining)
    {
	return true;
    }

    ssize_t got = read (io->fd, output->region.end, remaining);

    if (got <= 0)
    {
	if (got < 0)
	{
	    perror ("read");
	    *error = true;
	}

	return false;
    }

    output->region.end += got;

    assert ((size_t)range_count (output->region) <= limit);
    
    return true;
}

bool convert_write_fd (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit)
{
    convert_interface_fd * io = (convert_interface_fd*) interface;
    
    size_t remaining = range_count (output->region);

    if (!remaining)
    {
	return true;
    }

    ssize_t wrote = write (io->fd, output->region.begin, remaining);

    if (wrote < 0)
    {
	perror ("write");
	*error = true;
	return false;
    }

    if ((size_t)wrote < remaining)
    {
	output->region.begin += wrote;
    }
    else
    {
	output->region.begin = output->region.end = output->alloc.begin;
    }
    
    return true;
}

void convert_clear_fd (convert_interface * interface)
{
    convert_interface_fd * io = (convert_interface_fd*) interface;
    close (io->fd);
}
