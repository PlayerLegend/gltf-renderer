#include <stdbool.h>
#include <unistd.h>
#include "../../../glad/include/glad/glad.h"
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../vec/vec.h"
#include "../../vec/vec3.h"
#include "../../keyargs/keyargs.h"
#include "../../vec/mat4.h"
#include "../../json/json.h"
#include "../../gltf/gltf.h"
#include "../mesh/def.h"
#include "def.h"
#include "draw.h"

void gl_buffer_draw (gl_buffer * buffer, gl_view * view, int shader)
{
    range_typedef(gl_mesh, gl_mesh);

    range_gl_mesh meshes = { .begin = buffer->meshes, .end = buffer->meshes + buffer->mesh_count };

    gl_mesh * mesh;

    gl_mesh_instance ** instance;
    
    glBindBuffer (GL_ARRAY_BUFFER, buffer->vbo);
    glBindVertexArray(buffer->vao);

    struct {
	int model_translation;
	int model_rotation;
	int model_transform;
	int view_translation;
	int view_rotation;
	int view_transform;
	int projection;
	int mvp_rotation;
	int mvp_transform;
    }
	matrix_id =
    {
	.model_translation = glGetUniformLocation(shader, "uniform_model_translation"),
	.model_rotation = glGetUniformLocation(shader, "uniform_model_rotation"),
	.model_transform = glGetUniformLocation(shader, "uniform_model_transform"),

	.view_translation = glGetUniformLocation(shader, "uniform_view_translation"),
	.view_rotation = glGetUniformLocation(shader, "uniform_view_rotation"),
	.view_transform = glGetUniformLocation(shader, "uniform_view_transform"),

	.projection = glGetUniformLocation(shader, "uniform_projection"),
	
    	.mvp_rotation = glGetUniformLocation(shader, "uniform_mvp_rotation"),
	.mvp_transform = glGetUniformLocation(shader, "uniform_mvp_transform"),
    };
    
    struct {
	struct {
	    mat4 translation;
	    mat4 rotation;
	    mat4 transform;
	} model, view;

	struct {
	    mat4 rotation;
	    mat4 transform;
	}
	    mvp;

	mat4 projection;

	mat4 tmp;
    }
	matrix;

    mat4_setup_translation_matrix(.result = &matrix.view.translation, .translation = view->position);
    mat4_setup_rotation_matrix(.result = &matrix.view.rotation, .axis = view->axis);
    mat4_multiply (&matrix.view.transform, &matrix.view.translation, &matrix.view.rotation);

    mat4_setup_projection_matrix(.result = &matrix.projection,
				 .fovy = 2.0 * 3.14159 / (3.0 * 2),
				 .aspect = 1,
				 .near = 1,
				 .far = 10);
    
    glUniformMatrix4fv(matrix_id.view_rotation, 1, GL_FALSE, matrix.view.rotation);
    glUniformMatrix4fv(matrix_id.view_translation, 1, GL_FALSE, matrix.view.translation);
    glUniformMatrix4fv(matrix_id.view_transform, 1, GL_FALSE, matrix.view.transform);

    for_range (mesh, meshes)
    {
	for_range (instance, mesh->instances.region)
	{
	    mat4_setup_translation_matrix (.result = &matrix.model.translation, .translation = (*instance)->position);
	    mat4_setup_rotation_matrix (.result = &matrix.model.rotation, .axis = (*instance)->axis);

	    mat4_multiply (&matrix.model.transform, &matrix.model.translation, &matrix.model.rotation);
	    
	    //mat4_multiply (&matrix.mvp.rotation, &matrix.view.rotation, &matrix.model.rotation);
	    //mat4_multiply (&matrix.tmp, &matrix.model.transform, &matrix.view.transform);
	    //mat4_multiply (&matrix.mvp.transform, &matrix.tmp, &matrix.projection);
	    
	    glUniformMatrix4fv(matrix_id.model_rotation, 1, GL_FALSE, matrix.model.rotation);
	    glUniformMatrix4fv(matrix_id.model_translation, 1, GL_FALSE, matrix.model.translation);
	    glUniformMatrix4fv(matrix_id.model_transform, 1, GL_FALSE, matrix.model.transform);
    
	    glUniformMatrix4fv(matrix_id.mvp_rotation, 1, GL_FALSE, matrix.mvp.rotation);
	    glUniformMatrix4fv(matrix_id.mvp_transform, 1, GL_FALSE, matrix.mvp.transform);
	    glUniformMatrix4fv(matrix_id.projection, 1, GL_FALSE, matrix.projection);
	    
	    glDrawArrays (GL_TRIANGLES, mesh->index.begin, mesh->index.end);
	}
    }
}