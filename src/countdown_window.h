// ----------------------------------------------------------------------------
// countdown_window - Displays interval countdown and controls
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

// TBD: Rename this file, fix the comment header - JRS 8/20/13

#pragma once

#include <pebble_os.h>

// Initializes the countdown window. This will load any necessary resources and
// lay the window out, but will not display the window.

Window* countdown_window_init();

// Pushes the countdown window onto the window stack.

void countdown_window_push();
