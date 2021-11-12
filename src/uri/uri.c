#include <stdbool.h>
#include <stddef.h>
#include <fcntl.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "../convert/def.h"
#include "../convert/fd.h"
#include "uri.h"
#include "../log/log.h"

bool uri_load (window_unsigned_char * contents, const char * uri)
{
    int fd = open (uri, O_RDONLY);

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
    return true;
    
fail:
    return false;
}
