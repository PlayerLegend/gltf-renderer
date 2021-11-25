#include <stdbool.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../range/string.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "../window/vprintf.h"
#include "../window/printf.h"
#include "../window/string.h"
#include "../convert/def.h"
#include "../convert/fd.h"
#include "uri.h"
#include "../log/log.h"

static convert_interface * uri_open_file (const char * path)
{
    int fd = open (path, O_RDONLY);

    if (fd < 0)
    {
	perror (path);
	return NULL;
    }

    convert_interface_fd * fd_interface = calloc (1, sizeof(*fd_interface));

    *fd_interface = convert_interface_fd_init (fd);

    return &fd_interface->interface;
}

convert_interface * uri_open (const char * cwd, const char * format, ...)
{
    window_char uri = {0};
    
    {
	va_list ap;
	va_start (ap, format);
	window_vprintf (&uri, format, ap);
	va_end (ap);
    }

    convert_interface * retval = uri_open_file (uri.region.begin);

    if (!retval)
    {
	log_fatal ("Failed to open uri %s", uri.alloc.begin);
    }

    free (uri.alloc.begin);

    return retval;

fail:
    free (uri.alloc.begin);
    return NULL;
}

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

bool uri_realpath (window_char * path, const char * cwd, const char * format, ...)
{
    window_char uri = {0};

    if (cwd)
    {
	window_strcat (&uri, cwd);
    }
    else
    {
	window_rewrite (*path);
    }
    
    va_list ap;
    va_start (ap, format);
    window_vprintf_append (&uri, format, ap);
    va_end (ap);

    

    if (*uri.region.begin == '/')
    {
	window_strcat_range (path, &uri.region.const_cast);
    }
    
    free (uri.alloc.begin);
    return true;
    
//fail:
//    free (uri.alloc.begin);
//    return false;
}

/*
bool uri_load (window_unsigned_char * contents, const char * cwd, const char * format, ...)
{
    window_char uri = {0};

    va_list ap;
    va_start (ap, format);
    window_vprintf (&uri, format, ap);
    va_end (ap);
    
    int fd = open (uri.region.begin, O_RDONLY);

    if (fd < 0)
    {
	log_fatal ("Failed to open uri: %s", uri);
    }
    
    convert_interface_fd fd_read = convert_interface_fd_init(fd);
    bool error = false;

    if (!convert_load_all(&error, contents, &fd_read.interface))
    {
	convert_clear (&fd_read.interface);
	log_fatal ("Failed to load uri: %s", uri);
    }

    convert_clear (&fd_read.interface);
    free (uri.alloc.begin);
    return true;
    
fail:
    free (uri.alloc.begin);
    return false;
}
*/
