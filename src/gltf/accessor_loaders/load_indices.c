#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../../../glad/include/glad/glad.h"
#define FLAT_INCLUDES
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../range/def.h"
#include "../../window/def.h"
#include "GLfloat3.h"
#include "../../keyargs/keyargs.h"
#include "../../json/json.h"
#include "../../gltf/gltf.h"
#include "load_indices.h"
#include "../../window/alloc.h"
#include "../../log/log.h"

static void load_indices_from_uint8 (window_uint32_t * output, gltf_accessor_env * env)
{
    gltf_component component;
    
    for_gltf_accessor(component, *env)
    {
	*window_push(*output) = *component.u8;
    }
}

static void load_indices_from_uint16 (window_uint32_t * output, gltf_accessor_env * env)
{
    gltf_component component;
    
    for_gltf_accessor(component, *env)
    {
	*window_push(*output) = *component.u16;
    }
}

static void load_indices_from_uint32 (window_uint32_t * output, gltf_accessor_env * env)
{
    gltf_component component;
    
    for_gltf_accessor(component, *env)
    {
	*window_push(*output) = *component.u32;
    }
}

bool load_indices (window_uint32_t * output, gltf_accessor_env * env)
{
    if (env->type != GLTF_ACCESSOR_SCALAR)
    {
	log_fatal ("Index array does not contain scalars");
    }
    
    if (env->component_type == GLTF_ACCESSOR_COMPONENT_UNSIGNED_BYTE)
    {
	load_indices_from_uint8 (output, env);
    }
    else if (env->component_type == GLTF_ACCESSOR_COMPONENT_UNSIGNED_SHORT)
    {
	load_indices_from_uint16 (output, env);
    }
    else if (env->component_type == GLTF_ACCESSOR_COMPONENT_UNSIGNED_INT)
    {
	load_indices_from_uint32(output, env);
    }
    else
    {
	log_fatal ("Bad type for index array accessor");
    }

    return true;

fail:
    return false;
}
