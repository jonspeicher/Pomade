// ----------------------------------------------------------------------------
// pomodoro_controller - Implements the Pomodoro Technique sequence and timing
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

#include "cookies.h"
#include "countdown_controller.h"
#include "pomodoro_controller.h"

void pomodoro_controller_init(AppContextRef ctx) {
  countdown_controller_init(ctx);
}

void pomodoro_controller_timer_event(AppTimerHandle handle, uint32_t cookie) {
  // TBD: Is it worth retrieving this from the controller somehow? Would it
  // ever need to be chained? - JRS 8/15
  if (cookie == COUNTDOWN_COOKIE) {
    countdown_controller_timer_event(handle);
  }
}
