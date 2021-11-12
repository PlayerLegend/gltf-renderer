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
#endif

typedef struct gl_mesh gl_mesh;

typedef struct {
    GLuint begin;
    GLuint end;
}
    gl_mesh_index_range;

typedef struct {
    fvec3 position;
    fvec3 axis;
    gl_mesh * parent;
}
    gl_mesh_instance;

range_typedef(gl_mesh_instance*, gl_mesh_instance_p);
window_typedef(gl_mesh_instance*, gl_mesh_instance_p);

struct gl_mesh {
    gl_mesh_index_range index;
    window_gl_mesh_instance_p instances;
};

void mesh_instance_set_mesh (gl_mesh_instance * instance, gl_mesh * mesh);
