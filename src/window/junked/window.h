#ifndef FLAT_INCLUDES
#include <stddef.h>
#define FLAT_INCLUDES
#include "../array/range.h"
#endif

#define window_typedef(window_type, window_name, ...)	\
    typedef struct { range_##window_name region; range_##window_name alloc; __VA_ARGS__; } window_##window_name;

window_typedef(void, void);
window_typedef(char, char);
window_typedef(unsigned char, unsigned_char, window_char signed_cast);
