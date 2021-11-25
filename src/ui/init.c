#ifndef FLAT_INCLUDES
#include <stdbool.h>
#include "../../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#define FLAT_INCLUDES
#include "window.h"
#include "../log/log.h"
#endif

static void _error_callback(int error, const char* description)
{
    log_error ("Error: %s\n", description);
}

bool ui_init ()
{
    if (!glfwInit())
    {
	log_fatal ("glfw failed to init");
    }

    atexit (glfwTerminate);
    glfwSetErrorCallback (_error_callback);

    return true;
    
fail:
    return false;
}
