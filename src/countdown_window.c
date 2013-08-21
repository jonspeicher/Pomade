// ----------------------------------------------------------------------------
// countdown_window - Displays interval countdown and controls
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

// TBD: Rename this file, fix the comment header - JRS 8/20/13

#include <pebble_os.h>

// Define the debug name of this window.

#define WINDOW_DEBUG_NAME "countdown"

// Define the window itself.

static Window this_window;

// Public functions -----------------------------------------------------------

Window* countdown_window_init() {
  window_init(&this_window, WINDOW_DEBUG_NAME);
  return &this_window;
}

void countdown_window_push() {
  window_stack_push(&this_window, true);
}
