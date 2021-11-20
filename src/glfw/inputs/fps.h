#ifndef FLAT_INCLUDES
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../../vec/vec.h"
#include "../../vec/vec2.h"
#include "../../vec/vec3.h"
#endif

typedef struct inputs inputs;
struct inputs {
    fvec2 mouse_delta;
    fvec2 mouse_position;
    fvec3 relative_wish_motion;
};

extern inputs inputs_global;
