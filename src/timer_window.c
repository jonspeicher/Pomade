// ----------------------------------------------------------------------------
// timer_window - Initializes and displays the main timer window
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

// TBD: Consider this an "action window" and pass in the debug name - JRS 9/24

// Define the debug name of this window.

#define WINDOW_DEBUG_NAME "timer"

// Define the various user interface elements comprising this window.

static ActionBarLayer action_bar;

// Public functions -----------------------------------------------------------

void timer_window_init(Window* window) {
  window_init(window, WINDOW_DEBUG_NAME);
}

void timer_window_push(Window* window) {
  window_stack_push(window, true);
}

// TBD: Consider removing this or making it not act on a "singleton"- JRS 9/24

ActionBarLayer* timer_window_get_action_bar() {
  return &action_bar;
}
