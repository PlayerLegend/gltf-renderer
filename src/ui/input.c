#include <assert.h>
#include <stdbool.h>
#include "../../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#define FLAT_INCLUDES
#include "../vec/vec.h"
#include "../vec/vec2.h"
#include "../vec/vec3.h"
#include "button-id.h"
#include "window.h"
#include "input.h"
#include "../log/log.h"

typedef struct {
    ui_input_event_keyboard_button_callback callback;
    void * arg;
}
    ui_input_keyboard_button_bind;

typedef struct {
    ui_input_event_mouse_button_callback callback;
    void * arg;
}
    ui_input_mouse_button_bind;

typedef struct {
    ui_input_event_mouse_motion_callback callback;
    void * arg;
}
    ui_input_mouse_motion_bind;

static ui_input_keyboard_button_bind _keyboard_press_binds[KEYBOARD_BUTTON_ARRAY_COUNT];
static ui_input_mouse_button_bind _mouse_press_binds[MOUSE_BUTTON_ARRAY_COUNT];
static ui_input_keyboard_button_bind _keyboard_release_binds[KEYBOARD_BUTTON_ARRAY_COUNT];
static ui_input_mouse_button_bind _mouse_release_binds[MOUSE_BUTTON_ARRAY_COUNT];
static ui_input_mouse_motion_bind _mouse_motion_bind;
static ui_input_held_buttons _held_buttons;
static ui_input_event_mouse_motion _mouse_motion_event[2];
static bool _mouse_motion_select;

void ui_input_bind_keyboard_press (ui_input_keyboard_button_id id, ui_input_event_keyboard_button_callback callback, void * arg)
{
    _keyboard_press_binds[id] = (ui_input_keyboard_button_bind) { .callback = callback, .arg = arg };
    //log_debug ("bound %d with arg %p", id, _keyboard_press_binds[id].arg);
}

void ui_input_bind_keyboard_release (ui_input_keyboard_button_id id, ui_input_event_keyboard_button_callback callback, void * arg)
{
    _keyboard_release_binds[id] = (ui_input_keyboard_button_bind) { .callback = callback, .arg = arg };
}

void ui_input_bind_mouse_press (ui_input_mouse_button_id id, ui_input_event_mouse_button_callback callback, void * arg)
{
    _mouse_press_binds[id] = (ui_input_mouse_button_bind) { .callback = callback, .arg = arg };
}

void ui_input_bind_mouse_release (ui_input_mouse_button_id id, ui_input_event_mouse_button_callback callback, void * arg)
{
    _mouse_release_binds[id] = (ui_input_mouse_button_bind) { .callback = callback, .arg = arg };
}

void ui_input_bind_mouse_motion (ui_input_event_mouse_motion_callback callback, void * arg)
{
    _mouse_motion_bind = (ui_input_mouse_motion_bind){ .callback = callback, .arg = arg };
}

static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    ui_input_keyboard_button_bind * select = NULL;
    
    if (key < 0 || key >= KEYBOARD_BUTTON_ARRAY_COUNT - 1)
    {
	return;
    }
    
    if (action == GLFW_PRESS)
    {
	select = _keyboard_press_binds + key;
	_held_buttons.keyboard[key] = true;
    
    }
    else if (action == GLFW_RELEASE)
    {
	select = _keyboard_release_binds + key;
	_held_buttons.keyboard[key] = false;
    }

    //log_debug ("here %d %p %p", key, select, select->callback);
    
    if (select && select->callback)
    {
	ui_input_event_keyboard_button event =
	    {
		.previous_mouse_motion = _mouse_motion_event + !_mouse_motion_select,
		.held_buttons = &_held_buttons,
		.id = key,
	    };
    
	select->callback(&event, select->arg);
    }
}

static void _mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
    ui_input_mouse_button_bind * select = {0};

    if (button < 0 || button >= MOUSE_BUTTON_ARRAY_COUNT)
    {
	return;
    }
    
    if (action == GLFW_PRESS)
    {
	select = _mouse_press_binds + button;
	_held_buttons.mouse[button] = true;
    }
    else if (action == GLFW_RELEASE)
    {
	select = _mouse_release_binds + button;
	_held_buttons.mouse[button] = false;
    }

    if (select && select->callback)
    {
	ui_input_event_mouse_button event =
	    {
		.previous_motion = _mouse_motion_event + !_mouse_motion_select,
		.held_buttons = &_held_buttons,
		.id = button,
	    };
	
	select->callback(&event, select->arg);
    }
}

static void _cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    _mouse_motion_event[_mouse_motion_select].position = (fvec2) { xpos, ypos };
}

void ui_input_update()
{
    glfwPollEvents();

    ui_input_event_mouse_motion * current_event = _mouse_motion_event + _mouse_motion_select;
    ui_input_event_mouse_motion * old_event = _mouse_motion_event + !_mouse_motion_select;
    current_event->held_buttons = &_held_buttons;
    current_event->delta = (fvec2) vec2_subtract_init (current_event->position, old_event->position);
    current_event->previous_motion = old_event;

    _mouse_motion_bind.callback (current_event, _mouse_motion_bind.arg);

    _mouse_motion_select = !_mouse_motion_select;
}

void ui_input_init_window (ui_window * window)
{
    glfwSetKeyCallback((GLFWwindow*)window, _key_callback);
    glfwSetMouseButtonCallback((GLFWwindow*)window, _mouse_button_callback);
    glfwSetCursorPosCallback((GLFWwindow*)window, _cursor_position_callback);
}

void ui_input_lock_mouse (ui_window * window)
{
    glfwSetInputMode((GLFWwindow*)window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
