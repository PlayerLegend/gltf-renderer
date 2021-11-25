#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#endif

typedef struct convert_interface convert_interface;
typedef bool (*convert_update_func)(bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit);
typedef void (*convert_clear_func)(convert_interface * interface);
struct convert_interface {
    convert_update_func read;
    convert_update_func write;
    convert_clear_func clear;
};

convert_interface * convert_interface_new (size_t arg_size);

// return true if more can be read or written from arg, not necessarily into buffer

inline static bool convert_read (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit)
{
    return interface->read(error, output, interface, limit);
}

inline static bool convert_write (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit)
{
    return interface->write(error, output, interface, limit);
}

inline static void convert_clear (convert_interface * interface)
{
    interface->clear(interface);
}

void convert_free(convert_interface * interface);
bool convert_fill (bool * error, window_unsigned_char * output, convert_interface * interface);
bool convert_fill_limit (bool * error, window_unsigned_char * output, convert_interface * interface, size_t limit);
bool convert_drain (bool * error, window_unsigned_char * output, convert_interface * interface);
bool convert_load_all (bool * error, window_unsigned_char * output, convert_interface * interface);
