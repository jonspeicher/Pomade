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

  interval->minutes = minutes;
  interval->seconds = seconds;
  interval->time_remaining_sec = (minutes * 60) + seconds;

  update_fields(interval);
  interval->running = false;
  interval->complete = false;
}

void interval_reset(Interval* interval) {
  interval->time_remaining_sec = (interval->minutes * 60) + interval->seconds;
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
  if ((int) interval->time_remaining_sec - (int) seconds > 0) {
    interval->time_remaining_sec -= seconds;
  } else {
    interval->time_remaining_sec = 0;
  }
  update_fields(interval);
}

// Private functions ----------------------------------------------------------

void update_fields(Interval* interval) {
  unsigned int minutes_left, seconds_left;

  if (interval->time_remaining_sec == 0) {
    interval->complete = true;
  }
  minutes_left = interval->time_remaining_sec / 60;
  seconds_left = interval->time_remaining_sec % 60;
  snprintf(interval->time_left_string, INTERVAL_TIME_LEFT_STRING_NUM_CHARS + 1,
           INTERVAL_TIME_LEFT_STRING_FORMAT,
           minutes_left, seconds_left);
}
