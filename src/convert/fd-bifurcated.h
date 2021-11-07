#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../array/range.h"
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
    int fd_in;
    int fd_out;
}
    convert_interface_bifurcated_fd;

convert_interface_bifurcated_fd convert_interface_bifurcated_fd_init (int in, int out);
