#include "../../../../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../../../vec/vec.h"
#include "../../../vec/vec2.h"
#include "simple-mouse-wrapper.h"
#include "../../../log/log.h"

static fvec2 _mouse_position;

typedef struct {
    void * arg;
    void (*callback)(void * arg);
}
    key_action;

struct {
    key_action press;
    key_action release;
}
    _keyboard_action[GLFW_KEY_LAST + 1],
    _mouse_action[GLFW_MOUSE_BUTTON_LAST + 1];

static void _error_callback(int error, const char* description)
{
    log_error ("Error: %s\n", description);
}

bool init_graphics ()
{
    if (!glfwInit())
    {
	log_error ("glfw failed to init");
	return false;
    }

    atexit (glfwTerminate);
    glfwSetErrorCallback (_error_callback);

    return true;
}

static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    key_action select = {0};
    
    if (action == GLFW_PRESS)
    {
	select = _keyboard_action[key].press;
    }
    else if (action == GLFW_RELEASE)
    {
	select = _keyboard_action[key].release;
    }

    if (select.callback)
    {
	select.callback(select.arg);
    }
}

static void _mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
    key_action select = {0};
    
    if (action == GLFW_PRESS)
    {
	select = _mouse_action[button].press;
    }
    else if (action == GLFW_RELEASE)
    {
	select = _mouse_action[button].release;
    }

    if (select.callback)
    {
	select.callback(select.arg);
    }
}

static void _cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    _mouse_position.x = xpos;
    _mouse_position.y = ypos;
}

window * create_window ()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow * new_window = glfwCreateWindow (640, 480, "Test window", NULL, NULL);

    if (!new_window)
    {
	log_error ("Failed to create a window");
    }

    glfwMakeContextCurrent (new_window);

    if (!gladLoadGL())
    {
	log_normal ("glad failed to load GL");
	glfwDestroyWindow (new_window);
	return NULL;
    }

    glfwSetKeyCallback(new_window, _key_callback);
    glfwSetMouseButtonCallback(new_window, _mouse_button_callback);
    glfwSetCursorPosCallback(new_window, _cursor_position_callback);

    return (window*) new_window;
}

void set_current_window (window * window)
{
    glfwMakeContextCurrent ((GLFWwindow*) window);
}

void destroy_window (window * window)
{
    glfwDestroyWindow ((GLFWwindow*) window);
}

void swap_window (window * window)
{
    glfwSwapBuffers ((GLFWwindow*)window);
}

void inputs_update (inputs * in)
{
    glfwPollEvents ();

    in->mouse_delta = _mouse_position;
    vec2_subtract (in->mouse_delta, in->mouse_position);
    in->mouse_position = _mouse_position;

    /*if (in->mouse_delta.x > 100)
    {
	in->mouse_delta.x = 0;
    }
    
    if (in->mouse_delta.y > 100)
    {
	in->mouse_delta.y = 0;
	}*/
}

void inputs_reset (inputs * in)
{
    in->quit = false;
    in->mouse_delta = (fvec2){0,0};
    in->mouse_position = _mouse_position;
}

void inputs_lock_mouse (window * window)
{
    glfwSetInputMode((GLFWwindow*)window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool window_should_close (window * window)
{
    glfwPollEvents ();
    return glfwWindowShouldClose ((GLFWwindow*) window);
}

/*fvec wait_for_frame (int fps)
{
    static fvec last_time = 0;
    fvec current_time = glfwGetTime ();

    fvec have_delta = current_time - last_time;

    fvec want_delta = (fvec) 1 / (fvec) fps;

    fvec wait = want_delta - have_delta;

    
}
*/
