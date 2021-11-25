#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "def.h"
#include "env.h"
#include "../log/log.h"

bool gltf_accessor_env_setup (gltf_accessor_env * env, const glb_toc * toc, gltf_accessor * import_accessor)
{
    env->accessor = import_accessor;

    env->type = env->accessor->type;
    env->normalized = env->accessor->normalized;

    gltf_buffer_view * buffer_view = env->accessor->buffer_view;

    gltf_buffer * buffer = buffer_view->buffer;

    const unsigned char * buffer_data = toc->bin->data;

    if (buffer_data == toc->bin->data)
    {
	assert (buffer->byte_length <= toc->bin->length);
    }

    env->component_type = env->accessor->component_type;
    env->component_size = gltf_component_size (env->accessor->component_type);
    
    range_const_unsigned_char range_buffer = { .begin = buffer_data, .end = buffer_data + buffer->byte_length };

    range_const_unsigned_char range_buffer_view = { .begin = range_buffer.begin + buffer_view->byte_offset, .end = range_buffer_view.begin + buffer_view->byte_length };

    log_debug ("buffer_view byte stride: %d", buffer_view->byte_stride);
    log_debug ("else %d * %d = %d", env->component_size, env->type, env->component_size * env->type);
    env->byte_stride = !buffer_view->byte_stride ? (env->component_size * env->type) : buffer_view->byte_stride;
    

    log_debug ("%d mod %d * %d (=%d) == %d", env->byte_stride, env->component_size, env->type, env->component_size * env->type, env->byte_stride % (env->component_size * env->type));
    
    assert (env->byte_stride % (env->component_size * env->type) == 0);
    assert (env->byte_stride >= env->component_size * env->type);

    env->range.accessor.begin = range_buffer_view.begin + env->accessor->byte_offset;
    env->range.accessor.end = env->range.accessor.begin + env->accessor->count * env->byte_stride;

    log_debug ("%d vs %d", range_count(range_buffer_view), env->accessor->byte_offset + env->accessor->count * env->byte_stride);
    
    if (range_buffer_view.begin < range_buffer.begin || range_buffer.end < range_buffer_view.end)
    {
	log_fatal ("Buffer view range is out of bounds in gltf");
    }

    assert (env->range.accessor.begin >= range_buffer_view.begin);
    assert (range_buffer_view.end >= env->range.accessor.end);
    
    if (env->range.accessor.begin < range_buffer_view.begin || range_buffer_view.end < env->range.accessor.end)
    {
	log_fatal ("Accessor range is out of bounds in gltf");
    }

    return true;
    
fail:
    return false;
}
