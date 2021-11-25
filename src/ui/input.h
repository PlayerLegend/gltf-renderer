#ifndef FLAT_INCLUDES
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../vec/vec.h"
#include "../vec/vec2.h"
#include "../vec/vec3.h"
#include "button-id.h"
#include "window.h"
#endif

typedef struct {
    bool mouse[MOUSE_BUTTON_ARRAY_COUNT];
    bool keyboard[KEYBOARD_BUTTON_ARRAY_COUNT];
}
    ui_input_held_buttons;

typedef struct ui_input_event_mouse_motion ui_input_event_mouse_motion;

struct ui_input_event_mouse_motion {
    fvec2 delta;
    fvec2 position;
    const ui_input_held_buttons * held_buttons;
    const ui_input_event_mouse_motion * previous_motion;
};

typedef struct {
    const ui_input_event_mouse_motion * previous_motion;
    ui_input_mouse_button_id id;
    const ui_input_held_buttons * held_buttons;
}
    ui_input_event_mouse_button;

typedef struct {
    const ui_input_event_mouse_motion * previous_mouse_motion;
    ui_input_mouse_button_id id;
    const ui_input_held_buttons * held_buttons;
}
    ui_input_event_keyboard_button;

typedef void (*ui_input_event_keyboard_button_callback)(const ui_input_event_keyboard_button * button, void * arg);
typedef void (*ui_input_event_mouse_button_callback)(const ui_input_event_mouse_button * button, void * arg);
typedef void (*ui_input_event_mouse_motion_callback)(const ui_input_event_mouse_motion * motion, void * arg);

void ui_input_bind_keyboard_press (ui_input_keyboard_button_id id, ui_input_event_keyboard_button_callback callback, void * arg);
void ui_input_bind_keyboard_release (ui_input_keyboard_button_id id, ui_input_event_keyboard_button_callback callback, void * arg);

void ui_input_bind_mouse_press (ui_input_mouse_button_id id, ui_input_event_mouse_button_callback callback, void * arg);
void ui_input_bind_mouse_release (ui_input_mouse_button_id id, ui_input_event_mouse_button_callback callback, void * arg);

void ui_input_bind_mouse_motion (ui_input_event_mouse_motion_callback callback, void * arg);

void ui_input_update();

void ui_input_init_window (ui_window * window);

void ui_input_lock_mouse (ui_window * window);
