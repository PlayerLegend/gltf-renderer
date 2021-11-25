#ifndef FLAT_INCLUDES
#include "../../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#define FLAT_INCLUDES
#endif

double ui_get_time()
{
    return glfwGetTime();
}
