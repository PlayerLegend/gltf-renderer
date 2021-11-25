#ifndef FLAT_INCLUDES
#include <stdbool.h>
#define FLAT_INCLUDES
#endif

typedef struct ui_window ui_window;

ui_window * ui_window_new ();
bool ui_window_should_close (ui_window * window);
void ui_window_swap (ui_window * window);
void ui_window_destroy (ui_window * window);
