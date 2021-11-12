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
#include "../../json/json.h"
#include "../../gltf/gltf.h"
#include "../../uri/uri.h"
#include "../../log/log.h"
#include "accessor_loaders/GLfloat3.h"
#include "accessor_loaders/load_indices.h"
#include "accessor_loaders/load_GLfloat3.h"
#include "../../vec/mat4.h"
#include "../mesh/def.h"
#include "def.h"
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

static bool add_gltf (vbo_loader_buffers * buffers, const range_const_unsigned_char * contents)
{
    glb_toc toc;
    
    if (!glb_toc_load_memory (&toc, contents->char_cast.begin, range_count(*contents)))
    {
	log_fatal ("Failed to parse glb from input");
    }

    json_value * json_root = json_parse((const char*)toc.json->data, (const char*)toc.json->data + toc.json->length);

    if (!json_root)
    {
	log_fatal ("Failed to parse json from input");
    }

    gltf gltf;
    
    if (!gltf_from_json (&gltf, json_root))
    {
	log_fatal ("Failed to parse gltf from input");
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

    return true;
    
fail:
	return false;
}

static void free_buffers(vbo_loader_buffers * buffers)
{
    free (buffers->position.alloc.begin);
    free (buffers->normal.alloc.begin);
}

gl_buffer * gl_buffer_load (int uri_count, const char ** uris)
{
    assert (glGetError() == GL_NO_ERROR);
    
    window_unsigned_char uri_contents = {0};

    vbo_loader_buffers buffers = {0};
    
    for (int i = 0; i < uri_count; i++)
    {
	if (!uri_load (&uri_contents, uris[i]))
	{
	    log_fatal ("Failed to load uri %s", uris[i]);
	}

	add_gltf(&buffers, &uri_contents.region.const_cast);
    }

    size_t position_buffer_size = range_count (buffers.position.region) * sizeof(*buffers.position.region.begin);
    size_t normal_buffer_size = range_count (buffers.normal.region) * sizeof(*buffers.normal.region.begin);

    size_t vbo_size = position_buffer_size + normal_buffer_size;

    log_debug ("vbo size %zu", vbo_size);
    
    unsigned char * vbo_contents = calloc (1, vbo_size);

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

    if (false)
    {
	free (vbo_contents);
	free_buffers (&buffers);
    }

    return buffer;

fail:
    return NULL;
}

/*
void mesh_batch_draw (mesh_batch * batch, int shader)
{
    range_typedef(mesh,mesh);

    range_mesh meshes = { .begin = batch->meshes, .end = batch->meshes + batch->mesh_count };

    mesh * mesh;

    mesh_instance ** instance;
    
    glBindBuffer (GL_ARRAY_BUFFER, batch->vbo);
    glBindVertexArray(batch->vao);

    int translation_matrix_id = glGetUniformLocation(shader, "uniform_translation_matrix");
    int rotation_matrix_id = glGetUniformLocation(shader, "uniform_rotation_matrix");

    struct {
	mat4 translation;
	mat4 rotation;
    }
	matrix;

    for_range (mesh, meshes)
    {
	for_range (instance, mesh->instances.region)
	{
	    mat4_setup_translation_matrix (.result = &matrix.translation, .translation = { 0, 0.5 * sin(glfwGetTime()), 0 } );
	    mat4_setup_rotation_matrix(.result = &matrix.rotation, .axis = {cos(glfwGetTime()), sin(glfwGetTime()), 0});
	    
	    glUniformMatrix4fv(translation_matrix_id, 1, GL_FALSE, matrix.translation);
	    glUniformMatrix4fv(rotation_matrix_id, 1, GL_FALSE, matrix.rotation);
	    
	    glDrawArrays (GL_TRIANGLES, mesh->vertices.begin, mesh->vertices.end);
	}
    }
}
*/
