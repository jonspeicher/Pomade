// ----------------------------------------------------------------------------
// timer_window - Displays the main timer window and associated controls
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

// Define the debug name of this window.

#define WINDOW_DEBUG_NAME "timer"

// Define the window itself.

static Window this_window;

// Public functions -----------------------------------------------------------

Window* timer_window_init() {
  window_init(&this_window, WINDOW_DEBUG_NAME);
  return &this_window;
}

void timer_window_push() {
  window_stack_push(&this_window, true);
}
