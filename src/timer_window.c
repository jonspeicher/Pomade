// ----------------------------------------------------------------------------
// timer_window - Initializes and displays the main timer window
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

// Define the debug name of this window.

#define WINDOW_DEBUG_NAME "timer"

// Public functions -----------------------------------------------------------

void timer_window_init(Window* window) {
  window_init(window, WINDOW_DEBUG_NAME);
}

void timer_window_push(Window* window) {
  window_stack_push(window, true);
}
