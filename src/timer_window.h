// ----------------------------------------------------------------------------
// timer_window - Initializes and displays the main timer window
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Initializes the timer window. This will load any necessary resources and lay
// the window out, but will not display the window.

void timer_window_init(Window* window);

// Pushes the timer window onto the window stack.

void timer_window_push(Window* window);

// Returns access to the action bar that is part of the timer window.

ActionBarLayer* timer_window_get_action_bar();
