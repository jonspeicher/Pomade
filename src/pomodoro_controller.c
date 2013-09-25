// ----------------------------------------------------------------------------
// pomodoro_controller - Implements the pomodoro technique sequence and timing
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

#include "action_window.h"
#include "cookies.h"
#include "countdown_controller.h"
#include "pomodoro.h"
#include "pomodoro_config.h"
#include "pomodoro_controller.h"
#include "segment_view.h"

// Define the window that will be given to the controllers for view setup.

static Window action_window;

// Define a variable to track progress through the pomodoro technique.

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

  action_window_init(&action_window);

  segment_view_init(&action_window);
  segment_view_set_num_pomodoro_indicators(POMODORO_COUNT_FOR_LONG_BREAK);
  segment_view_show_segment_type(pomodoro.this_segment->type);

  countdown_controller_init(ctx, &action_window);
  countdown_controller_set_countdown_handlers(handlers);
  countdown_controller_set_interval(&pomodoro.this_segment->interval);

  action_window_push(&action_window);
}

void pomodoro_controller_deinit(AppContextRef ctx) {
  countdown_controller_deinit(ctx);
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
  pomodoro_start_segment(&pomodoro);
  countdown_controller_set_interval(&pomodoro.this_segment->interval);
  countdown_controller_restart_on_abort(pomodoro.this_segment->restart_on_abort);
  segment_view_show_segment_type(pomodoro.this_segment->type);
  segment_view_set_pomodoros_completed(pomodoro.pomodoros_completed);
}

void countdown_complete_handler() {
  vibes_long_pulse();
  pomodoro_complete_segment(&pomodoro);
  segment_view_set_pomodoros_completed(pomodoro.pomodoros_completed);
}

void countdown_abort_handler() {
  vibes_double_pulse();
  pomodoro_abort_segment(&pomodoro);
}
