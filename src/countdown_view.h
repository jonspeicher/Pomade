// ----------------------------------------------------------------------------
// countdown_view - Displays a countdown timer and controls
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>
#include "action_window.h"

// Creates the countdown view and adds it to the window specified. The click
// config provider parameter sets the click config provider for the view, which
// will be invoked whenever the view needs to update the click configuration.

void countdown_view_init(ActionWindow* window, ClickConfigProvider provider);

// Sets the time remaining to be displayed on the countdown view. If the time
// remaining will not fit on the view's display, it will be truncated. A call
// to this function will only have an effect after the view is initialized.

void countdown_view_set_time_remaining_sec(unsigned int seconds);

// Shows the "start" state of the countdown view.

void countdown_view_show_start();

// Shows the "restart" state of the countdown view.

void countdown_view_show_restart();

// Shows the "abort" state of the countdown view.

void countdown_view_show_abort();
