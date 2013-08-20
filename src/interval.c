// ----------------------------------------------------------------------------
// interval - Provides data structures and methods for manipulating intervals
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include "interval.h"

// Public functions -----------------------------------------------------------

void interval_init(Interval* interval, unsigned int minutes, unsigned int seconds) {
  if (minutes > INTERVAL_MAX_DURATION_MIN) minutes = INTERVAL_MAX_DURATION_MIN;
  if (seconds > INTERVAL_MAX_DURATION_SEC) seconds = INTERVAL_MAX_DURATION_SEC;

  interval->minutes = minutes;
  interval->seconds = seconds;
  interval_reset(interval);
}

void interval_reset(Interval* interval) {
  interval->running = false;
  interval->complete = false;
  interval->time_remaining_sec = (interval->minutes * 60) + interval->seconds;
}

void interval_start(Interval* interval) {
  interval->running = true;
}

void interval_abort(Interval* interval) {
  interval->running = false;
}

void interval_decrement_by_seconds(Interval* interval, unsigned int seconds) {
  int time_remaining_sec = (int) interval->time_remaining_sec - (int) seconds;

  if (time_remaining_sec > 0) {
    interval->time_remaining_sec = time_remaining_sec;
  } else {
    interval->time_remaining_sec = 0;
    interval->complete = true;
  }
}
