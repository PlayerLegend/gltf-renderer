#ifndef FLAT_INCLUDES
#include <stdbool.h>
#include <unistd.h>
#include "../../../glad/include/glad/glad.h"
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../keyargs/keyargs.h"
#include "../../json/json.h"
#include "../../gltf/gltf.h"
#include "../mesh/def.h"
#include "def.h"
#endif

typedef struct {
    fvec3 position;
    fvec3 axis;
    float fov;
}
    gl_view;

void gl_buffer_draw (gl_buffer * buffer, gl_view * view, int shader);
