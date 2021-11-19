#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include "../../../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../vec/vec.h"
#include "../../vec/vec2.h"
#include "../../vec/vec3.h"
#include "../../vec/vec4.h"
#include "../../keyargs/keyargs.h"
#include "../../vec/mat4.h"
#include "../../vec/view.h"
#include "../../json/json.h"
#include "../../gltf/gltf.h"
#include "../mesh/def.h"
#include "../buffer/def.h"
#include "../buffer/draw.h"
#include "../buffer/loader.h"
#include "../../log/log.h"
#include "../triangle/glfw/simple-mouse-wrapper.h"
#include "../triangle/load-shader.h"

int main(int argc, char * argv[])
{
    init_graphics();
    window * window = create_window();
    
    if (argc != 2)
    {
	log_stderr ("Usage: %s [file]", argv[0]);
    }

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    gl_buffer * buffer = gl_buffer_load(1, (const char**)argv + 1);
    
    int vertex_fd = open ("src/gl/gltf-renderer/default.vert", O_RDONLY);

    assert (vertex_fd >= 0);
    
    int fragment_fd = open ("src/gl/gltf-renderer/default.frag", O_RDONLY);

    assert (fragment_fd >= 0);
    
    GLuint program_id = load_shader_program (vertex_fd, fragment_fd);
    
    assert (buffer);
    
    assert (glGetError() == GL_NO_ERROR);
    //while((err = glGetError()) != GL_NO_ERROR)

    gl_mesh_instance instance = {0};
    gl_view view = { .quaternion = { 0, 0, 0, 1 } };

    mesh_instance_set_mesh(&instance, buffer->meshes);

    instance.quaternion = (fvec4){ 0, 0, 0, 1 };
       
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    //int transform_matrix_location = glGetUniformLocation(program_id, "uniform_transform_matrix");
    
    glUseProgram (program_id);

    inputs inputs = {0};
    
    inputs_lock_mouse (window);
    inputs_reset (&inputs);

    view_normals view_normals;
    fvec3 view_axis_add_vec;
    fvec3 view_axis_add_scale;
    fvec3 view_axis_add_part;
    
    while (!window_should_close (window))
    {
	//float sway = sin(glfwGetTime());
	
	inputs_update (&inputs);

	//view.position.z = sway;
	//instance.position.z = -3;
	//instance.position.y = sway / 10;
	//instance.position.x = sway;

	view_normals_setup(&view_normals, &view.quaternion);
	
	//log_normal ("%f [%f %f %f]", vec3_dot (view_normals.right, view_normals.up), view_normals.forward.x, view_normals.forward.y, view_normals.forward.z);

	view_axis_add_scale = (fvec3)
	{
	    .y = (float) inputs.mouse_delta.y / 1000.0,
	    .x = (float) inputs.mouse_delta.x / 1000.0
	};

	fvec3 up = { 0, 1, 0 }; //view_normals.up;
	view_axis_add_part = (fvec3) vec3_scale_init (up, view_axis_add_scale.x);
	view_axis_add_vec = view_axis_add_part;

	fvec3 right = { 1, 0, 0 }; //view_normals.right;
	view_axis_add_part = (fvec3) vec3_scale_init (right, view_axis_add_scale.y);
	vec3_add (view_axis_add_vec, view_axis_add_part);

	fvec4 new_quaternion;
	vec4_setup_rotation_quaternion(&new_quaternion, &view_axis_add_vec);

	//log_debug ("rotation %f", new_quaternion.w);
	
	//view_axis_add(&view.axis, &view_axis_add_vec);
	//view.axis = view_axis_add_vec;

	vec4_apply_rotation_quaternion(&view.quaternion, &new_quaternion);

	//instance.position = (fvec3) vec3_scale_init(view.axis, sway / 15.0);

	log_normal ("modify: %f %f %f %f", new_quaternion.x, new_quaternion.y, new_quaternion.z, new_quaternion.w);
	//log_normal ("Quaternion: %f %f %f %f", view.quaternion.x, view.quaternion.y, view.quaternion.z, view.quaternion.w);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
	gl_buffer_draw(buffer, &view, program_id);
	
	assert (glGetError() == GL_NO_ERROR);
	swap_window (window);
    }

    destroy_window(window);

    return 0;
}
