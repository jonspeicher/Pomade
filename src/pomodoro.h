// ----------------------------------------------------------------------------
// pomodoro - Defines a model to track progress through the Pomodoro Technique
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include "pomodoro_interval.h"

// Defines a structure type to hold the pomodoro technique segments.

typedef struct {
  PomodoroInterval* current_segment;
  PomodoroInterval pomodoro;
  PomodoroInterval rest; // TBD These will be interval eventually - JRS 8/27
} Pomodoro;

// Initializes the pomodoro technique structure.

void pomodoro_init(Pomodoro* pomodoro);

// Completes the current pomodoro technique segment and causes an advance to
// the next segment in the pomodoro technique sequence.

void pomodoro_complete_segment(Pomodoro* pomodoro);
