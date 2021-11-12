#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include "../../../glad/include/glad/glad.h"
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../keyargs/keyargs.h"
#include "../../json/json.h"
#include "../../gltf/gltf.h"
#include "def.h"
#include "../../window/alloc.h"

void mesh_instance_set_mesh (gl_mesh_instance * instance, gl_mesh * mesh)
{
    if (instance->parent)
    {
	assert (!range_is_empty(instance->parent->instances.region));

	gl_mesh_instance ** i;
	for_range(i, instance->parent->instances.region)
	{
	    if (*i == instance)
	    {
		*i = *(--instance->parent->instances.region.end);
		break;
	    }
	}
    }
    
    *window_push(mesh->instances) = instance;
    instance->parent = mesh;
}
