// ----------------------------------------------------------------------------
// countdown_controller - Controls arbitrary interval countdown and display
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

#include "action_window.h"
#include "interval.h"

// Defines the signature of a countdown event handler.

typedef void (*CountdownHandler)();

// Defines a structure to contain configured countdown event handlers.
//
//   started: invoked BEFORE resetting and commencing countdown of the interval
//   complete: invoked AFTER completion of interval countdown
//   aborted: invoked AFTER interval countdown is aborted

typedef struct {
  CountdownHandler started;
  CountdownHandler complete;
  CountdownHandler aborted;
} CountdownHandlers;

// Initializes the countdown controller.

void countdown_controller_init(AppContextRef ctx, ActionWindow* window);

// De-initializes the countdown controller.

void countdown_controller_deinit(AppContextRef ctx);

// Sets the countdown event handlers. These will be invoked when an executing
// countdown completes or is aborted.

void countdown_controller_set_countdown_handlers(CountdownHandlers handlers);

// Sets the countdown interval. No state-based validation is performed so that
// if the countdown is running while this function is called it may cause the
// displayed countdown to jump, stop, or change state abruptly. Once the
// interval is given to the countdown controller, the controller will manage
// interval state changes and countdowns in accordance with user input.

void countdown_controller_set_interval(Interval* interval);

// Sets whether the countdown controller presents a restart action if the
// currently-running countdown is aborted. When set to false, a start action
// follows an abort.

void countdown_controller_restart_on_abort(bool restart_on_abort);

// Informs the countdown controller that its timer event has occurred. The main
// application is responsible for handling timer events and forwarding them
// along to the appropriate controllers.

void countdown_controller_timer_event(AppTimerHandle handle);
