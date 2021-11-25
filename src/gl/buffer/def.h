#ifndef FLAT_INCLUDES
#include <stdbool.h>
#include <unistd.h>
#include "../../../glad/include/glad/glad.h"
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../vec/vec4.h"
#include "../mesh/def.h"
#endif

typedef struct gl_buffer gl_buffer;

void gl_buffer_mesh_access (range_gl_mesh * result, gl_buffer * target);
