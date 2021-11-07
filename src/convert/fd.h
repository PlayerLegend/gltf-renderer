#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "def.h"
#endif

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

#ifndef STDERR_FILENO
#define STDERR_FILENO 2
#endif

typedef struct {
    convert_interface interface;
    int fd;
}
    convert_interface_fd;

bool convert_read_fd (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit);
bool convert_write_fd (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit);
void convert_clear_fd (convert_interface * interface);

static inline convert_interface_fd convert_interface_fd_init (int fd)
{
    return (convert_interface_fd)
    {
	.interface.read = convert_read_fd,
	.interface.write = convert_write_fd,
	.interface.clear = convert_clear_fd,
	.fd = fd,
    };
}
