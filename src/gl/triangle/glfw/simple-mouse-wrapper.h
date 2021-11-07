#ifndef FLAT_INCLUDES
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../../../vec/vec.h"
#include "../../../vec/vec2.h"
#endif

typedef struct window window;

typedef struct inputs inputs;
struct inputs {
    bool quit;
    fvec2 mouse_delta;
    fvec2 mouse_position;
};

void inputs_update (inputs * in);
void inputs_reset (inputs * in);

bool init_graphics ();
window * create_window ();
void set_current_window (window * window);
void destroy_window (window * window);
void swap_window (window * window);
bool window_should_close (window * window);
