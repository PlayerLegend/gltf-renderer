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
#include "../../json/def.h"
#include "../../gltf/def.h"
#include "../mesh/def.h"
#include "../buffer/def.h"
#include "../buffer/draw.h"
#include "../buffer/loader.h"
#include "../../log/log.h"
#include "../../ui/init.h"
#include "../../ui/window.h"
#include "../../ui/button-id.h"
#include "../../ui/input.h"
#include "../../ui/time.h"
#include "../triangle/load-shader.h"

typedef struct {
    gl_view view;
    view_normals view_normals;
}
    inputs_arg;

void inputs_mouse_motion_callback (const ui_input_event_mouse_motion * event, void * arg_void)
{
    inputs_arg * arg = arg_void;

    fvec2 mouse_motion = { event->delta.x / 1000.0, event->delta.y / 1000.0 };

    //log_debug ("delta %f %f", mouse_motion.x, mouse_motion.y);
    
    fvec3 up = vec3_scale_init(arg->view_normals.up, mouse_motion.x);
    fvec3 right = vec3_scale_init(arg->view_normals.right, mouse_motion.y);

    fvec3 axis = vec3_add_init (up, right);

    //log_debug ("axis %f %f %f", axis.x, axis.y, axis.z);
    
    vec4_apply_rotation_axis(&arg->view.quaternion, &axis);
    view_normals_setup(&arg->view_normals, &arg->view.quaternion);
}

void move_view_right (inputs_arg * arg)
{
    fvec3 delta = vec3_scale_init(arg->view_normals.right, 0.1);
    vec3_add(arg->view.position, delta);
}

void move_view_left (inputs_arg * arg)
{
    fvec3 delta = vec3_scale_init(arg->view_normals.right, -0.1);
    vec3_add(arg->view.position, delta);
}

void move_view_forward (inputs_arg * arg)
{
    fvec3 delta = vec3_scale_init(arg->view_normals.forward, 0.1);
    vec3_add(arg->view.position, delta);
    //log_debug ("pointer %p", arg);
    log_debug ("fw %f %f %f", arg->view.position.x, arg->view.position.y, arg->view.position.z);
    //log_debug ("fw %f %f %f %f", arg->view.quaternion.x, arg->view.quaternion.y, arg->view.quaternion.z, arg->view.quaternion.w);
}

void move_view_back (inputs_arg * arg)
{
    fvec3 delta = vec3_scale_init(arg->view_normals.forward, -0.1);
    vec3_add(arg->view.position, delta);
}

void inputs_key_left_callback (const ui_input_event_keyboard_button * event, void * arg_void)
{
    move_view_left (arg_void);
}

void inputs_key_right_callback (const ui_input_event_keyboard_button * event, void * arg_void)
{
    move_view_right (arg_void);
}

void inputs_key_forward_callback (const ui_input_event_keyboard_button * event, void * arg_void)
{
    move_view_forward (arg_void);
}

void inputs_key_back_callback (const ui_input_event_keyboard_button * event, void * arg_void)
{
    move_view_back (arg_void);
}

int gltf_renderer(int argc, char * argv[])
{
    if (!ui_init())
    {
	return 1;
    }
    
    ui_window * window = ui_window_new();
    
    if (argc != 3)
    {
	log_stderr ("Usage: %s [file]", argv[0]);
    }

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    gl_buffer * buffer = gl_buffer_load(argc - 1, (const char**)argv + 1);
    
    int vertex_fd = open ("src/gl/gltf-renderer/default.vert", O_RDONLY);

    assert (vertex_fd >= 0);
    
    int fragment_fd = open ("src/gl/gltf-renderer/default.frag", O_RDONLY);

    assert (fragment_fd >= 0);
    
    GLuint program_id = load_shader_program (vertex_fd, fragment_fd);
    
    assert (buffer);
    
    assert (glGetError() == GL_NO_ERROR);
    //while((err = glGetError()) != GL_NO_ERROR)

    gl_mesh_instance world_instance = { .scale = 1 };
    gl_mesh_instance object_instance = { .scale = 1 };

    inputs_arg inputs_arg = { .view.quaternion = { 0, 0, 0, 1 } };
    view_normals_setup(&inputs_arg.view_normals, &inputs_arg.view.quaternion);

    range_gl_mesh meshes;

    gl_buffer_mesh_access (&meshes, buffer);

    log_debug ("Mesh count %d", range_count(meshes));
    assert (range_count(meshes) == 2);

    mesh_instance_set_mesh (&world_instance, meshes.begin);
    mesh_instance_set_mesh (&object_instance, meshes.begin + 1);

    world_instance.quaternion = (fvec4){ 0, 0, 0, 1 };
       
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glUseProgram (program_id);

    ui_input_lock_mouse (window);

    ui_input_bind_mouse_motion(inputs_mouse_motion_callback, &inputs_arg);
    ui_input_bind_keyboard_press('W', inputs_key_forward_callback, &inputs_arg);
    ui_input_bind_keyboard_press('D', inputs_key_left_callback, &inputs_arg);
    ui_input_bind_keyboard_press('S', inputs_key_back_callback, &inputs_arg);
    ui_input_bind_keyboard_press('A', inputs_key_right_callback, &inputs_arg);
    log_debug ("pointer a %p", &inputs_arg);
    
    while (!ui_window_should_close (window))
    {
	world_instance.scale = 1.5 + sin(ui_get_time ());
	ui_input_update ();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
	gl_buffer_draw(buffer, &inputs_arg.view, program_id);
	
	assert (glGetError() == GL_NO_ERROR);
	ui_window_swap (window);
	//log_debug ("position %f %f %f", inputs_arg.view.position.x,
	//	   inputs_arg.view.position.y,
	//	   inputs_arg.view.position.z);
    }

    gl_buffer_free (buffer);
    ui_window_destroy(window);

    return 0;
}

int main(int argc, char * argv[])
{
    return gltf_renderer (argc, argv);
}
