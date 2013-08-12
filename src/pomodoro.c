// ----------------------------------------------------------------------------
// pomodoro - Provides data structures and methods for manipulating pomodoros
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <stdio.h>
#include "pomodoro.h"

// Define the duration of a pomodoro.

#define POMODORO_INITIAL_TIME_MIN 25
#define POMODORO_INITIAL_TIME_SEC POMODORO_INITIAL_TIME_MIN * 60

// Define the format for a pomodoro's time remaining display string.

#define POMODORO_TIME_LEFT_STRING_FORMAT "%d:%02d"

// Private functions.

static void update_fields(Pomodoro* pomodoro);

// Public functions -----------------------------------------------------------

void pomodoro_init(Pomodoro* pomodoro) {
  pomodoro->total_seconds_left = POMODORO_INITIAL_TIME_SEC;
  update_fields(pomodoro);
}

void pomodoro_decrement_by_seconds(Pomodoro* pomodoro, unsigned int seconds) {
  if ((int) pomodoro->total_seconds_left - (int) seconds > 0) {
    pomodoro->total_seconds_left -= seconds;
  } else {
    pomodoro->total_seconds_left = 0;
  }
  update_fields(pomodoro);
}

// Private functions ----------------------------------------------------------

void update_fields(Pomodoro* pomodoro) {
  pomodoro->minutes_left = pomodoro->total_seconds_left / 60;
  pomodoro->seconds_left = pomodoro->total_seconds_left % 60;
  snprintf(pomodoro->time_left_string, POMODORO_TIME_LEFT_STRING_NUM_CHARS + 1,
           POMODORO_TIME_LEFT_STRING_FORMAT,
           pomodoro->minutes_left, pomodoro->seconds_left);
}
