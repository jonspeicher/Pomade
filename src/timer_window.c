// ----------------------------------------------------------------------------
// timer_window - Initializes and displays the main timer window
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

// TBD: The z-order bug is back; fix it this time by adding layers to this
// window via a specific method that puts them below the action bar - JRS 9/24

#include <pebble_os.h>

// TBD: Consider this an "action window" and pass in the debug name - JRS 9/24

// Define the debug name of this window.

#define WINDOW_DEBUG_NAME "timer"

// Define the various user interface elements comprising this window.

static ActionBarLayer action_bar;

// Public functions -----------------------------------------------------------

void timer_window_init(Window* window) {
  window_init(window, WINDOW_DEBUG_NAME);
  action_bar_layer_init(&action_bar);
  action_bar_layer_add_to_window(&action_bar, window);
}

void timer_window_push(Window* window) {
  window_stack_push(window, true);
}

// TBD: Consider removing this or making it not act on a "singleton"- JRS 9/24

ActionBarLayer* timer_window_get_action_bar() {
  return &action_bar;
}
