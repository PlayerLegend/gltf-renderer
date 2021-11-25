#ifndef FLAT_INCLUDES
#include <stdbool.h>
#include <stddef.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "../convert/def.h"
#endif

convert_interface * uri_open (const char * cwd, const char * format, ...);
bool uri_realpath (window_char * path, const char * cwd, const char * format, ...);
