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
#endif

typedef struct {
    GLuint vbo;
    GLuint vao;
    size_t mesh_count;
    size_t vertex_count;
    gl_mesh meshes[];
}
    gl_buffer;
