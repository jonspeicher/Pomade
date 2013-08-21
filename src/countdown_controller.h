// ----------------------------------------------------------------------------
// countdown_controller - Controls arbitrary interval countdown and display
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>
#include "interval.h"

// Initializes the countdown controller.

void countdown_controller_init(AppContextRef ctx, Window* window);

// Sets the countdown interval. No state-based validation is performed so that
// if the countdown is running while this function is called it may cause the
// displayed countdown to jump, stop, or change state abruptly.

void countdown_controller_set_interval(Interval* interval);

// Informs the countdown controller that its timer event has occurred. The main
// application is responsible for handling timer events and forwarding them
// along to the appropriate controllers.

void countdown_controller_timer_event(AppTimerHandle handle);
