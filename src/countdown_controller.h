// ----------------------------------------------------------------------------
// countdown_controller - Controls arbitrary interval countdown and display
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Initializes the countdown controller. This will also push the countdown
// window on to the window stack.

void countdown_controller_init(AppContextRef ctx);

// Informs the countdown controller that its timer event has occurred. The main
// application must be responsible for handling timer events destined for this
// application and forwarding them along with the appropriate timer handle to
// the countdown controller.

void countdown_controller_timer_event(AppTimerHandle handle);
