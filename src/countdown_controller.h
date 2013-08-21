// ----------------------------------------------------------------------------
// countdown_controller - Controls arbitrary interval countdown and display
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Initializes the countdown controller.

void countdown_controller_init(AppContextRef ctx, Window* window);

// Informs the countdown controller that its timer event has occurred. The main
// application is responsible for handling timer events and forwarding them
// along to the appropriate controllers.

void countdown_controller_timer_event(AppTimerHandle handle);
