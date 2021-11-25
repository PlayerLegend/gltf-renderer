#ifndef FLAT_INCLUDES
#include <stdbool.h>
#include "../../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#define FLAT_INCLUDES
#include "../vec/vec.h"
#include "../vec/vec2.h"
#include "window.h"
#include "button-id.h"
#include "input.h"
#include "../log/log.h"
#endif

ui_window * ui_window_new ()
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
    
    ui_input_init_window ((ui_window*)new_window);

    return (ui_window*) new_window;
}

bool ui_window_should_close (ui_window * window)
{
    glfwPollEvents ();
    return glfwWindowShouldClose ((GLFWwindow*) window);
}

void ui_window_swap (ui_window * window)
{
    glfwSwapBuffers ((GLFWwindow*)window);
}

void ui_window_destroy (ui_window * window)
{
    glfwDestroyWindow ((GLFWwindow*) window);
}
