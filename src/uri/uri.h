#ifndef FLAT_INCLUDES
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#endif

bool uri_load (window_unsigned_char * contents, const char * cwd, const char * format, ...);
bool uri_realpath (window_char * path, const char * cwd, const char * format, ...);
