// ----------------------------------------------------------------------------
// countdown_window - Displays interval countdown and controls
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Initializes the countdown window. This will load any necessary resources and
// lay the window out, but will not display the window. The click config
// provider parameter sets the click config provider for the window, which will
// be invoked whenever the window needs to update the click configuration.

void countdown_window_init(ClickConfigProvider provider);

// Pushes the countdown window onto the window stack.

void countdown_window_push();

// Sets the time remaining to be displayed on the countdown window. Note that
// no validation is done to ensure that the time remaining string will fit on
// the window's display, and a call to this function will only have an effect
// after the window is initialzed.

void countdown_window_set_time_remaining(char* time_remaining);

// Shows the "abort" state of the countdown window.

void countdown_window_show_abort();

// Shows the "restart" state of the countdown window.

void countdown_window_show_restart();
