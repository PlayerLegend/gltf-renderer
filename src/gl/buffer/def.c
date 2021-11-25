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
#include "def.h"
#include "internal/def.h"

void gl_buffer_mesh_access (range_gl_mesh * result, gl_buffer * target)
{
    result->begin = target->meshes;
    result->end = result->begin + target->mesh_count;
}
