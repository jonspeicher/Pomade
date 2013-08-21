// ----------------------------------------------------------------------------
// timer_window - Displays the main timer window and associated controls
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Initializes the timer window. This will load any necessary resources and lay
// the window out, but will not display the window.

Window* timer_window_init();

// Pushes the timer window onto the window stack.

void timer_window_push();
