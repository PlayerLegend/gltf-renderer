#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../convert/def.h"
#endif

bool tokenizer_read (bool * error, window_char * token, window_unsigned_char * buffer, convert_interface * source);
