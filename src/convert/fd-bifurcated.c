#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../array/range.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "def.h"
#include "fd-bifurcated.h"

#include "../log/log.h"

bool convert_read_bifurcated_fd (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit)
{
    convert_interface_bifurcated_fd * io = (convert_interface_bifurcated_fd*) interface;
    
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

    ssize_t got = read (io->fd_in, output->region.end, remaining);

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

bool convert_write_bifurcated_fd (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit)
{
    convert_interface_bifurcated_fd * io = (convert_interface_bifurcated_fd*) interface;
    
    size_t remaining = range_count (output->region);

    if (!remaining)
    {
	return true;
    }

    ssize_t wrote = write (io->fd_out, output->region.begin, remaining);

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

convert_interface_bifurcated_fd convert_interface_bifurcated_fd_init (int in, int out)
{
    return (convert_interface_bifurcated_fd)
    {
	.interface.read = convert_read_bifurcated_fd,
	.interface.write = convert_write_bifurcated_fd,
	.fd_in = in,
	.fd_out = out,
    };
}
