// ----------------------------------------------------------------------------
// pomodoro - Provides data structures and methods for manipulating pomodoros
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

// Defines the number of characters in a pomodoro time left display string. Note
// that this does not account for the terminating NULL character.

#define POMODORO_TIME_LEFT_STRING_NUM_CHARS 5

// Defines a pomodoro. Pomodoros consist primarily of the countdown timer and
// associated display strings.

typedef struct {
  unsigned int total_seconds_left;
  unsigned int minutes_left;
  unsigned int seconds_left;
  char time_left_string[POMODORO_TIME_LEFT_STRING_NUM_CHARS + 1];
} Pomodoro;

// Initializes a pomodoro. This initializes the time remaining and sets the
// display string appropriately.

void pomodoro_init(Pomodoro* pomodoro);

// Decrements the time remaining in the pomodoro by the number of seconds
// specified. If the requested decrement is greater than the number of seconds
// remaining, the time remaining is set to zero.

void pomodoro_decrement_by_seconds(Pomodoro* pomodoro, unsigned int seconds);
