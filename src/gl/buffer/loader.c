#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../window/alloc.h"
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../keyargs/keyargs.h"
#include "../../json/def.h"
#include "../../gltf/def.h"
#include "../../gltf/env.h"
#include "../../gltf/parse.h"
#include "../../convert/def.h"
#include "../../gltf/convert.h"
#include "../../uri/uri.h"
#include "../../log/log.h"
#include "../../gltf/accessor_loaders/GLfloat3.h"
#include "../../gltf/accessor_loaders/load_indices.h"
#include "../../gltf/accessor_loaders/load_GLfloat3.h"
#include "../../vec/vec4.h"
#include "../../vec/mat4.h"
#include "../mesh/def.h"
#include "def.h"
#include "internal/def.h"
#include "loader.h"

typedef struct {
    window_GLuint start_index;
    window_uint32_t indices;
    window_GLfloat3 position;
    window_GLfloat3 normal;
}
    vbo_loader_buffers;

static bool add_primitive_position (window_GLfloat3 * position, range_uint32_t * indices, const glb_toc * toc, gltf_mesh_primitive * primitive)
{
    gltf_accessor_env env;

    gltf_accessor_env_setup (&env, toc, primitive->attributes.position);

    return load_GLfloat3(position, indices, &env);
}

static bool add_primitive_normal (window_GLfloat3 * position, range_uint32_t * indices, const glb_toc * toc, gltf_mesh_primitive * primitive)
{
    gltf_accessor_env env;

    gltf_accessor_env_setup (&env, toc, primitive->attributes.normal);

    return load_GLfloat3(position, indices, &env);
}

static bool add_primitive (vbo_loader_buffers * buffers, const glb_toc * toc, gltf_mesh_primitive * primitive)
{
    gltf_accessor_env env;

    gltf_accessor_env_setup(&env, toc, primitive->indices);

    window_rewrite (buffers->indices);
    load_indices (&buffers->indices, &env);
    
    return
	add_primitive_position (&buffers->position, &buffers->indices.region, toc, primitive) &&
	add_primitive_normal (&buffers->normal, &buffers->indices.region, toc, primitive);
}

static bool add_gltf_mesh (vbo_loader_buffers * buffers, const glb_toc * toc, gltf_mesh * mesh)
{
    gltf_mesh_primitive * primitive;

    for_range (primitive, mesh->primitives)
    {
	if (!add_primitive (buffers, toc, primitive))
	{
	    return false;
	}
    }

    return true;
}

static bool add_mesh_from_interface (vbo_loader_buffers * buffers, convert_interface * interface)
{
    glb_toc toc;
    gltf gltf;

    window_unsigned_char bytes_buffer = {0};

    if (!gltf_load_from_interface(&gltf, &toc, &bytes_buffer, interface))
    {
	return false;
    }

    *window_push(buffers->start_index) = range_count(buffers->position.region);

    gltf_mesh * mesh;

    for_range (mesh, gltf.meshes)
    {
	if (!add_gltf_mesh (buffers, &toc, mesh))
	{
	    log_fatal ("Failed to add mesh %d", range_index(mesh, gltf.meshes));
	}
    }

    free (bytes_buffer.alloc.begin);
    gltf_clear (&gltf);
    return true;

fail:
    free (bytes_buffer.alloc.begin);
    gltf_clear (&gltf);
    return false;
}

static void free_buffers(vbo_loader_buffers * buffers)
{
    free (buffers->start_index.alloc.begin);
    free (buffers->indices.alloc.begin);
    free (buffers->position.alloc.begin);
    free (buffers->normal.alloc.begin);
}

static bool load_vbo_loader_buffers (vbo_loader_buffers * buffers, int uri_count, const char ** uris)
{
    convert_interface * uri_interface;

    bool success;
    
    for (int i = 0; i < uri_count; i++)
    {
	uri_interface = uri_open (NULL, "%s", uris[i]);

	if (!uri_interface)
	{
	    return false;
	}
	
	success = add_mesh_from_interface (buffers, uri_interface);

	convert_free (uri_interface);

	if (!success)
	{
	    return false;
	}
    }

    return true;
}

gl_buffer * gl_buffer_load (int uri_count, const char ** uris)
{
    assert (glGetError() == GL_NO_ERROR);
    
    vbo_loader_buffers buffers = {0};

    unsigned char * vbo_contents = NULL;
    
    if (!load_vbo_loader_buffers (&buffers, uri_count, uris))
    {
	log_fatal ("Could not load a specified mesh uri for drawing");
    }
    
    size_t position_buffer_size = range_count (buffers.position.region) * sizeof(*buffers.position.region.begin);
    size_t normal_buffer_size = range_count (buffers.normal.region) * sizeof(*buffers.normal.region.begin);

    size_t vbo_size = position_buffer_size + normal_buffer_size;

    vbo_contents = calloc (1, vbo_size);

    memcpy (vbo_contents, buffers.position.region.begin, position_buffer_size);
    memcpy (vbo_contents + position_buffer_size, buffers.normal.region.begin, normal_buffer_size);
    
    gl_buffer * buffer = calloc (1, sizeof(*buffer) + uri_count * sizeof(gl_mesh));

    assert (uri_count == range_count (buffers.start_index.region));

    buffer->mesh_count = uri_count;
    buffer->vertex_count = range_count (buffers.position.region);
    
    GLuint * index;
    for_range (index, buffers.start_index.region)
    {
	buffer->meshes[range_index(index, buffers.start_index.region)] = (gl_mesh)
	{
	    .index = { .begin = *index, .end = index + 1 < buffers.start_index.region.begin ? index[1] : buffer->vertex_count },
	};
    }
    
    glGenBuffers (1, &buffer->vbo);
    glGenVertexArrays (1, &buffer->vao);
    glBindVertexArray(buffer->vao);
    
    glBindBuffer (GL_ARRAY_BUFFER, buffer->vbo);
    glBufferData (GL_ARRAY_BUFFER, vbo_size, vbo_contents, GL_STATIC_DRAW);
    
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray (1);
    
    assert (glGetError() == GL_NO_ERROR);

    free_buffers (&buffers);
    free (vbo_contents);

    return buffer;

fail:
    free (vbo_contents);
    free_buffers (&buffers);
    return NULL;
}

void gl_buffer_free (gl_buffer * target)
{
    glDeleteVertexArrays (1, &target->vao);
    glDeleteBuffers (1, &target->vbo);

    struct range(gl_mesh) meshes = { .begin = target->meshes, .end = target->meshes + target->mesh_count };
    gl_mesh * mesh;
    gl_mesh_instance ** instance;

    for_range (mesh, meshes)
    {
	for_range (instance, mesh->instances.region)
	{
	    (*instance)->parent = NULL;
	}
	free (mesh->instances.alloc.begin);
    }

    free (target);
}
