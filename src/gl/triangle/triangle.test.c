#include <stdbool.h>
#include <unistd.h>
#include "../../../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#define FLAT_INCLUDES
#include "../../vec/vec.h"
#include "../../vec/vec2.h"
#include "../../vec/vec3.h"
#include "glfw/simple-mouse-wrapper.h"
#include "../../log/log.h"
#include "load-shader.h"
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../window/alloc.h"

typedef struct {
    size_t have_count;
    size_t max_count;
    window_unsigned_char buffer;
}
    va_buffer;



range_typedef(fvec3, fvec3);

void va_buffer_alloc_vertex_count (va_buffer * buffer, size_t count)
{
    buffer->max_count = count;
    buffer->have_count = 0;
    size_t alloc_size = (1 + 2) * (3 * sizeof (GLfloat)) * count;
    log_debug ("Alloc %zu", alloc_size);
    window_alloc (buffer->buffer, alloc_size);
    buffer->buffer.region = buffer->buffer.alloc;
    log_debug("alloc result: %zu", range_count(buffer->buffer.region));
}

void va_buffer_set_position (va_buffer * dest, const fvec3 * input)
{
    GLfloat * set_array = ((GLfloat*) dest->buffer.region.begin) + 3 * dest->have_count;
    set_array[0] = input->x;
    set_array[1] = input->y;
    set_array[2] = input->z;
}

void va_buffer_set_normal (va_buffer * dest, const fvec3 * input)
{
    GLfloat * set_array = ((GLfloat*) dest->buffer.region.begin) + 3 * dest->max_count + 2 * 3 * dest->have_count;
    set_array[0] = input->x;
    set_array[1] = input->y;
    set_array[2] = input->z;
}

void va_buffer_set_color (va_buffer * dest, const fvec3 * input)
{
    GLfloat * set_array = ((GLfloat*) dest->buffer.region.begin) + 3 * dest->max_count + 2 * 3 * dest->have_count + 3;
    set_array[0] = input->x;
    set_array[1] = input->y;
    set_array[2] = input->z;
}

GLuint setup_vbo_from_va_buffer (GLuint VBO, va_buffer * input)
{
    assert (input->have_count == input->max_count);

    log_debug("binding: %zu, maxcount %zu", range_count(input->buffer.region), input->max_count);
    
    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER, range_count (input->buffer.region), input->buffer.region.begin, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray (0);

    // normal
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat) * input->max_count));
    glEnableVertexAttribArray (1);
    
    // color
    glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat) * (input->max_count + 1)));
    glEnableVertexAttribArray (2);

    return VBO;
}

void dump_va_buffer (va_buffer * input)
{
    GLfloat * array = (GLfloat*) input->buffer.region.begin;
    GLfloat * vector;
    for (size_t i = 0; i < input->max_count * 3; i++)
    {
	vector = array + 3 * i;
	vector = array + 3 * i;
	log_normal ("fvec3: %f, %f, %f", vector[0], vector[1], vector[2]);
    }
    log_normal ("");
    
    for (size_t i = 0; i < input->max_count; i++)
    {
	vector = array + 3 * i;
	log_normal ("Position: %f, %f, %f", vector[0], vector[1], vector[2]);
	
	vector = array + 3 * input->max_count + 2 * 3 * i;
	log_normal ("Normal: %f, %f, %f", vector[0], vector[1], vector[2]);

	vector = array + 3 * input->max_count + 2 * 3 * i + 3;
	log_normal ("Color: %f, %f, %f", vector[0], vector[1], vector[2]);

	log_normal ("");
    }
}

void setup_vbo2(GLuint VBO)
{
    GLfloat vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
    };
    
    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void setup_va_buffer (va_buffer * output)
{
    fvec3 position_array[] =
    {
	{ -1.0f, -1.0f, 0.0f },
	{ 1.0f, -1.0f, 0.0f },
	{ 0.0f,  1.0f, 0.0f },
/*	{ -0.5f, -0.5f, 0.0f },
	{ 0.5f, -0.5f, 0.0f },
	{ 0.0f,  0.5f, 0.0f },*/
    };

    fvec3 color_array[] =
    {
	{ 1, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 0, 1 },
    };

    va_buffer_alloc_vertex_count(output, 3);
    
    while (output->have_count < output->max_count)
    {
	log_debug ("%d / %d", output->have_count, output->max_count);
	
	static const fvec3 null_fvec3 = {0};
	va_buffer_set_position(output, position_array + output->have_count);
	va_buffer_set_color(output, color_array + output->have_count);
	va_buffer_set_normal(output, &null_fvec3);
	
	output->have_count++;
    }

    dump_va_buffer (output);
}

void setup_vbo (GLuint VBO)
{
    va_buffer va_buffer = {0};

    setup_va_buffer (&va_buffer);
    
    setup_vbo_from_va_buffer (VBO, &va_buffer);

    //free (va_buffer.buffer.alloc.begin);
}

int main()
{
    init_graphics();

    window * window = create_window ();
    
    if (!window)
    {
	log_error ("Failed to init graphics");
	exit (1);
    }

    GLuint VAO;
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glGenVertexArrays (1, &VAO);

    glBindVertexArray (VAO);

    GLuint VBO;
    glGenBuffers (1, &VBO);
    setup_vbo(VBO);
    
    int vertex_fd = open ("src/gl/triangle/triangle.vert", O_RDONLY);
    int fragment_fd = open ("src/gl/triangle/triangle.frag", O_RDONLY);

    GLuint program_id = load_shader_program (vertex_fd, fragment_fd);
    
    assert (glGetError() == GL_NO_ERROR);
    //while((err = glGetError()) != GL_NO_ERROR)
       
    while (!window_should_close (window))
    {    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        	
	glUseProgram (program_id);
	glBindBuffer (GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glDrawArrays (GL_TRIANGLES, 0, 3);

	assert (glGetError() == GL_NO_ERROR);
	swap_window (window);
    }
    

    /*while (!window_should_close (window))
    {    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram (program_id);

	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glDrawArrays (GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray (0);

	swap_window (window);
	}*/
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program_id);
    
    destroy_window (window);
    
    return 0;
    
//fail:
    //  return 1;
}

int main2()
{
    init_graphics();

    window * window = create_window ();
    
    if (!window)
    {
	log_error ("Failed to init graphics");
	exit (1);
    }

    GLuint vertex_array_id;
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glGenVertexArrays (1, &vertex_array_id);
    glBindVertexArray (vertex_array_id);

    GLfloat vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
    };

    GLuint vertex_buffer;
    glGenBuffers (1, &vertex_buffer);
    glBindBuffer (GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    int vertex_fd = open ("src/gl/triangle/triangle.vert", O_RDONLY);
    int fragment_fd = open ("src/gl/triangle/triangle.frag", O_RDONLY);

    GLuint program_id = load_shader_program (vertex_fd, fragment_fd);
    
    while (!window_should_close (window))
    {    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram (program_id);

	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glDrawArrays (GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray (0);

	swap_window (window);
    }

    return 0;
}
