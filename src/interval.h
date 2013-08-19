// ----------------------------------------------------------------------------
// interval - Provides data structures and methods for manipulating intervals
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <stdbool.h>

// Defines the number of characters in an interval time left display string.
// Note that this does not account for the terminating NULL character.

#define INTERVAL_TIME_LEFT_STRING_NUM_CHARS 5

// Define the maximum supported interval value. Note that this is primarily a
// function of the number of characters supported by the time left string.

#define INTERVAL_MAX_DURATION_MIN 99
#define INTERVAL_MAX_DURATION_SEC 59

// Defines an interval. Intervals consist primarily of the countdown timer and
// associated display strings, plus flags to track the state of the interval.

typedef struct {
  bool running;
  bool complete;
  unsigned int minutes;
  unsigned int seconds;
  unsigned int time_remaining_sec;
  char time_left_string[INTERVAL_TIME_LEFT_STRING_NUM_CHARS + 1];
} Interval;

// Initializes an interval to the number of minutes and seconds remaining.

void interval_init(Interval* interval, unsigned int minutes, unsigned int seconds);

// Resets an interval to its initially-configured duration. This will also mark
// the interval as not running and not complete.

void interval_reset(Interval* interval);

// Starts an interval.

void interval_start(Interval* interval);

// Aborts an interval.

void interval_abort(Interval* interval);

// Decrements the time remaining in the interval by the number of seconds
// specified. If the requested decrement is greater than the number of seconds
// remaining, the time remaining is set to zero.

void interval_decrement_by_seconds(Interval* interval, unsigned int seconds);
