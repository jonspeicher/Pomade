// ----------------------------------------------------------------------------
// pomodoro_controller - Implements the Pomodoro Technique sequence and timing
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

#include "cookies.h"
#include "countdown_controller.h"
#include "interval.h"
#include "pomodoro_controller.h"
#include "timer_window.h"

// TBD: This is going to need to get state feedback about the countdown and
// whether it completes or is aborted so that it can manage the pomodoro ->
// break -> long break sequence - JRS 8/20

static Interval pomodoro;

void pomodoro_controller_init(AppContextRef ctx) {
  interval_init(&pomodoro, 25, 0);
  countdown_controller_init(ctx, timer_window_init());
  countdown_controller_set_interval(&pomodoro);
  timer_window_push();
}

void pomodoro_controller_timer_event(AppTimerHandle handle, uint32_t cookie) {
  // TBD: Is it worth retrieving this from the controller somehow? Would it
  // ever need to be chained? - JRS 8/15
  if (cookie == COUNTDOWN_COOKIE) {
    countdown_controller_timer_event(handle);
  }
}
