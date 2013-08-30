// ----------------------------------------------------------------------------
// pomodoro_controller - Implements the pomodoro technique sequence and timing
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Initializes the pomodoro controller. This will also push the main pomodoro
// timing window on to the window stack.

void pomodoro_controller_init(AppContextRef ctx);

// Informs the pomodoro controller that a timer event has occurred. The main
// application is responsible for handling timer events and forwarding them
// along to the appropriate controllers.

void pomodoro_controller_timer_event(AppTimerHandle handle, uint32_t cookie);
