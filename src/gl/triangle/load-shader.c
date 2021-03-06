#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define FLAT_INCLUDES
#include "../../../glad/include/glad/glad.h"
#include "load-shader.h"
#include "../../vec/vec.h"
#include "../../vec/vec2.h"
#include "glfw/simple-mouse-wrapper.h"
#include "../../range/def.h"
#include "../../log/log.h"
#include "../../window/def.h"
#include "../../convert/def.h"
#include "../../convert/fd.h"

static GLuint _build_shader (const char * file_contents, GLenum shader_type)
{
    GLuint shader_id = glCreateShader (shader_type);

    glShaderSource (shader_id, 1, &file_contents, NULL);
    glCompileShader (shader_id);

    GLint result = GL_FALSE;
    int info_log_length;
    
    glGetShaderiv (shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 0)
    {
	char * info_log = malloc (info_log_length + 1);
	glGetShaderInfoLog (shader_id, info_log_length, NULL, info_log);
	log_normal ("%s", info_log);
	free (info_log);
    }

    if (result != GL_TRUE)
    {
	log_normal ("Failed to build the shader");
	return GL_FALSE;
    }

    return shader_id;
}

GLuint load_shader_program (int vertex_fd, int fragment_fd)
{
    convert_interface_fd fd_read = convert_interface_fd_init(vertex_fd);

    window_unsigned_char file_contents = {0};

    log_normal ("Building vertex shader");

    bool error = false;

    if (!convert_load_all(&error, &file_contents, &fd_read.interface))
    {
	log_fatal ("Failed to read vertex shader");
    }

    //log_normal ("Shader contents: %.*s", range_count(file_contents.region), file_contents.region.begin);
    
    GLuint vertex_id = _build_shader (file_contents.signed_cast.region.begin, GL_VERTEX_SHADER);

    if (vertex_id == GL_FALSE)
    {
	goto fail;
    }

    log_normal ("Building fragment shader");

    convert_clear(&fd_read.interface);

    fd_read = convert_interface_fd_init (fragment_fd);

    window_rewrite(file_contents);
    
    if (!convert_load_all(&error, &file_contents, &fd_read.interface))
    {
	log_error ("Failed to read fragment shader");
	goto fail;
    }

    //log_normal ("Shader contents: %.*s", range_count(file_contents.region), file_contents.region.begin);

    GLuint fragment_id = _build_shader (file_contents.signed_cast.region.begin, GL_FRAGMENT_SHADER);
    
    if (fragment_id == GL_FALSE)
    {
	goto fail;
    }

    log_normal ("Linking shader program");
    GLuint program_id = glCreateProgram();
    glAttachShader (program_id, vertex_id);
    glAttachShader (program_id, fragment_id);
    glLinkProgram (program_id);

    GLint result;
    int info_log_length;
    
    glGetProgramiv (program_id, GL_LINK_STATUS, &result);
    glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 0)
    {
	char * info_log = malloc (info_log_length + 1);
	glGetProgramInfoLog (program_id, info_log_length, NULL, info_log);
	log_normal ("%s", info_log);
	free (info_log);
    }

    if (result != GL_TRUE)
    {
	log_error ("Failed to link shader program");
	goto fail;
    }

    glDetachShader (program_id, vertex_id);
    glDetachShader (program_id, fragment_id);

    glDeleteShader (vertex_id);
    glDeleteShader (fragment_id);

    free (file_contents.alloc.begin);
    convert_clear(&fd_read.interface);

    return program_id;

fail:
    convert_clear(&fd_read.interface);
    free (file_contents.alloc.begin);
    return GL_FALSE;
}
