#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "def.h"
#endif

bool convert_getline (bool * error, range_const_char * line, window_unsigned_char * buffer, convert_interface * interface, const range_const_char * end_sequence);
