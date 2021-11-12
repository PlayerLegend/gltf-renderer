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
#include "../../keyargs/keyargs.h"
#include "../../vec/mat4.h"
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
    gl_view view = {0};

    mesh_instance_set_mesh(&instance, buffer->meshes);
       
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    //int transform_matrix_location = glGetUniformLocation(program_id, "uniform_transform_matrix");
    
    glUseProgram (program_id);

    inputs inputs = {0};

    inputs_lock_mouse (window);
    
    while (!window_should_close (window))
    {
	float sway = sin(glfwGetTime());
	
	inputs_update (&inputs);

	//view.position.z = sway;
	instance.position.z = -3;
	instance.position.x = sway;
	
	view.axis.y += inputs.mouse_delta.x / 1000;
	view.axis.x += inputs.mouse_delta.y / 1000;
	    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
	gl_buffer_draw(buffer, &view, program_id);
	
	assert (glGetError() == GL_NO_ERROR);
	swap_window (window);
    }

    destroy_window(window);

    return 0;
}
