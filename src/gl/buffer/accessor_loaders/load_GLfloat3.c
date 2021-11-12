
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../../../../glad/include/glad/glad.h"
#define FLAT_INCLUDES
#include "../../../vec/vec.h"
#include "../../../vec/vec3.h"
#include "../../../range/def.h"
#include "../../../window/def.h"
#include "GLfloat3.h"
#include "../../../keyargs/keyargs.h"
#include "../../../json/json.h"
#include "../../../gltf/gltf.h"
#include "load_indices.h"
#include "load_GLfloat3.h"
#include "../../../log/log.h"
#include "../../../window/alloc.h"

static bool load_GLfloat3_from_uint8 (window_GLfloat3 * output, range_uint32_t * indices, gltf_accessor_env * env)
{
    gltf_component component;

    uint32_t * index;

    for_range (index, *indices)
    {
	component.pointer = env->range.accessor.begin + env->byte_stride * (*index);

	if ( (void*)(component.u8 + 1) > (void*)env->range.accessor.end)
	{
	    log_fatal ("Index to vertex attributes is out of bounds");
	}

	*window_push(*output) = (GLfloat3)
	    {
		.x = (GLfloat) component.u8[0] / (GLfloat) 255,
		.y = (GLfloat) component.u8[1] / (GLfloat) 255,
		.z = (GLfloat) component.u8[2] / (GLfloat) 255,
	    };
    }

    return true;
    
fail:
    return false;
}

static bool load_GLfloat3_from_int8 (window_GLfloat3 * output, range_uint32_t * indices, gltf_accessor_env * env)
{
    gltf_component component;

    uint32_t * index;

    for_range (index, *indices)
    {
	component.pointer = env->range.accessor.begin + env->byte_stride * (*index);

	if ( (void*)(component.i8) + 1 > (void*)env->range.accessor.end)
	{
	    log_fatal ("Index to vertex attributes is out of bounds");
	}

	*window_push(*output) = (GLfloat3)
	    {
		.x = (GLfloat) component.i8[0] / (GLfloat) 127,
		.y = (GLfloat) component.i8[1] / (GLfloat) 127,
		.z = (GLfloat) component.i8[2] / (GLfloat) 127,
	    };
    }

    return true;
    
fail:
    return false;
}

static bool load_GLfloat3_from_uint16 (window_GLfloat3 * output, range_uint32_t * indices, gltf_accessor_env * env)
{
    gltf_component component;

    uint32_t * index;

    for_range (index, *indices)
    {
	component.pointer = env->range.accessor.begin + env->byte_stride * (*index);

	if ( (void*)(component.u16 + 1) > (void*)env->range.accessor.end)
	{
	    log_fatal ("Index to vertex attributes is out of bounds");
	}

	*window_push(*output) = (GLfloat3)
	    {
		.x = (GLfloat) component.u16[0] / (GLfloat) 65535,
		.y = (GLfloat) component.u16[1] / (GLfloat) 65535,
		.z = (GLfloat) component.u16[2] / (GLfloat) 65535,
	    };
    }

    return true;
    
fail:
    return false;
}

static bool load_GLfloat3_from_int16 (window_GLfloat3 * output, range_uint32_t * indices, gltf_accessor_env * env)
{
    gltf_component component;

    uint32_t * index;

    for_range (index, *indices)
    {
	component.pointer = env->range.accessor.begin + env->byte_stride * (*index);

	if ( (void*)(component.i16 + 1) > (void*)env->range.accessor.end)
	{
	    log_fatal ("Index to vertex attributes is out of bounds");
	}

	*window_push(*output) = (GLfloat3)
	    {
		.x = (GLfloat) component.i16[0] / (GLfloat) 32767,
		.y = (GLfloat) component.i16[1] / (GLfloat) 32767,
		.z = (GLfloat) component.i16[2] / (GLfloat) 32767,
	    };
    }

    return true;
    
fail:
    return false;
}

static bool load_GLfloat3_from_float (window_GLfloat3 * output, range_uint32_t * indices, gltf_accessor_env * env)
{
    gltf_component component;

    uint32_t * index;

    for_range (index, *indices)
    {
	component.pointer = env->range.accessor.begin + env->byte_stride * (*index);

	if ( (void*)(component.f + 1) > (void*)env->range.accessor.end)
	{
	    log_fatal ("Index to vertex attributes is out of bounds");
	}

	*window_push(*output) = (GLfloat3)
	    {
		.x = component.f[0],
		.y = component.f[1],
		.z = component.f[2],
	    };
    }

    return true;
    
fail:
    return false;
}

bool load_GLfloat3 (window_GLfloat3 * output, range_uint32_t * indices, gltf_accessor_env * env)
{
    if (env->normalized)
    {
	if (env->component_type == GLTF_ACCESSOR_COMPONENT_BYTE)
	{
	    return load_GLfloat3_from_int8 (output, indices, env);
	}
	else if (env->component_type == GLTF_ACCESSOR_COMPONENT_UNSIGNED_BYTE)
	{
	    return load_GLfloat3_from_uint8 (output, indices, env);
	}
	else if (env->component_type == GLTF_ACCESSOR_COMPONENT_SHORT)
	{
	    return load_GLfloat3_from_int16 (output, indices, env);
	}
	else if (env->component_type == GLTF_ACCESSOR_COMPONENT_UNSIGNED_SHORT)
	{
	    return load_GLfloat3_from_uint16 (output, indices, env);
	}
	
	log_fatal ("Bad type for normalized integer accessor");
    }
    else
    {
	if (env->component_type == GLTF_ACCESSOR_COMPONENT_FLOAT)
	{
	    return load_GLfloat3_from_float(output, indices, env);
	}

	log_fatal ("Bad type for non-normalizd accessor");
    }

fail:
    return false;
}
