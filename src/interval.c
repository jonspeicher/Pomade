// ----------------------------------------------------------------------------
// interval - Provides data structures and methods for manipulating intervals
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include "interval.h"

// Define the format for an interval's time left display string.

#define INTERVAL_TIME_LEFT_STRING_FORMAT "%d:%02d"

// Private functions.

static void update_fields(Interval* interval);

// Public functions -----------------------------------------------------------

void interval_init(Interval* interval, unsigned int minutes, unsigned int seconds) {
  if (minutes > INTERVAL_MAX_DURATION_MIN) minutes = INTERVAL_MAX_DURATION_MIN;
  if (seconds > INTERVAL_MAX_DURATION_SEC) seconds = INTERVAL_MAX_DURATION_SEC;

  interval->minutes_left = minutes;
  interval->seconds_left = seconds;
  interval->total_seconds_left = (minutes * 60) + seconds;

  update_fields(interval);
  interval->running = false;
  interval->complete = false;
}

void interval_start(Interval* interval) {
  interval->running = true;
}

void interval_abort(Interval* interval) {
  interval->running = false;
}

void interval_decrement_by_seconds(Interval* interval, unsigned int seconds) {
  if ((int) interval->total_seconds_left - (int) seconds > 0) {
    interval->total_seconds_left -= seconds;
  } else {
    interval->total_seconds_left = 0;
  }
  update_fields(interval);
}

// Private functions ----------------------------------------------------------

void update_fields(Interval* interval) {
  if (interval->total_seconds_left == 0) {
    interval->complete = true;
  }
  interval->minutes_left = interval->total_seconds_left / 60;
  interval->seconds_left = interval->total_seconds_left % 60;
  snprintf(interval->time_left_string, INTERVAL_TIME_LEFT_STRING_NUM_CHARS + 1,
           INTERVAL_TIME_LEFT_STRING_FORMAT,
           interval->minutes_left, interval->seconds_left);
}
