// ----------------------------------------------------------------------------
// pomodoro_controller - Implements the Pomodoro Technique sequence and timing
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

#include "cookies.h"
#include "countdown_controller.h"
#include "interval.h"
#include "pomodoro_config.h"
#include "pomodoro_controller.h"
#include "timer_window.h"

// Define the window that will be given to the controllers for view setup.

static Window timer_window;

// Define the intervals that this controller will use.

static Interval pomodoro;
static Interval rest;
static Interval* current_interval;

// Private functions.

void countdown_start_handler();
void countdown_complete_handler();
void countdown_abort_handler();

// Public functions -----------------------------------------------------------

void pomodoro_controller_init(AppContextRef ctx) {
  CountdownHandlers handlers = {
    .started = countdown_start_handler,
    .complete = countdown_complete_handler,
    .aborted = countdown_abort_handler
  };

  interval_init(&pomodoro, POMODORO_MINUTES, POMODORO_SECONDS);
  interval_init(&rest, REST_MINUTES, REST_SECONDS);
  current_interval = &pomodoro;

  timer_window_init(&timer_window);
  countdown_controller_init(ctx, &timer_window);
  countdown_controller_set_countdown_handlers(handlers);
  countdown_controller_set_interval(current_interval);
  timer_window_push(&timer_window);
}

void pomodoro_controller_timer_event(AppTimerHandle handle, uint32_t cookie) {
  // TBD: Is it worth retrieving this from the controller somehow? Would it
  // ever need to be chained? - JRS 8/15
  if (cookie == COUNTDOWN_COOKIE) {
    countdown_controller_timer_event(handle);
  }
}

// Private functions ----------------------------------------------------------

void countdown_start_handler() {
  countdown_controller_set_interval(current_interval);
}

void countdown_complete_handler() {
  vibes_long_pulse();
  current_interval = (current_interval == &pomodoro) ? &rest : &pomodoro;
}

void countdown_abort_handler() {
  vibes_double_pulse();
  if (current_interval == &rest) {
    current_interval = &pomodoro;
  }
}
