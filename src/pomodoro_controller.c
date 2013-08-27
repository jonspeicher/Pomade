// ----------------------------------------------------------------------------
// pomodoro_controller - Implements the Pomodoro Technique sequence and timing
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

#include "cookies.h"
#include "countdown_controller.h"
#include "pomodoro.h"
#include "pomodoro_controller.h"
#include "pomodoro_interval.h"
#include "timer_window.h"

// Define the window that will be given to the controllers for view setup.

static Window timer_window;

// Define a structure to track progress through the pomodoro technique.

static Pomodoro pomodoro;

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

  pomodoro_init(&pomodoro);

  timer_window_init(&timer_window);
  countdown_controller_init(ctx, &timer_window);
  countdown_controller_set_countdown_handlers(handlers);
  countdown_controller_set_interval(&pomodoro.current_segment->interval);
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
  countdown_controller_set_interval(&pomodoro.current_segment->interval);
  if (pomodoro.current_segment->restart_on_abort) {
    countdown_controller_set_abort_action_to_restart();
  } else {
    countdown_controller_set_abort_action_to_start();
  }
}

void countdown_complete_handler() {
  vibes_long_pulse();
  pomodoro.current_segment = (pomodoro.current_segment == &pomodoro.pomodoro) ?
    &pomodoro.rest: &pomodoro.pomodoro;
}

void countdown_abort_handler() {
  vibes_double_pulse();
  if (pomodoro.current_segment == &pomodoro.rest) {
    pomodoro.current_segment = &pomodoro.pomodoro;
  }
}
