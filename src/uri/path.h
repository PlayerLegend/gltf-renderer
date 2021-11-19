#ifndef FLAT_INCLUDES
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#endif

bool resolve_path (window_char * output, const char * cwd, window_char * input);
