// ----------------------------------------------------------------------------
// pomodoro_interval - Provides intervals specific to the Pomodoro Technique
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <stdbool.h>
#include "interval.h"

// Defines a pomodoro-technique-specific interval. This is a standard interval
// with an additional flag to indicate if the interval should be restarted
// after it is aborted.

typedef struct {
  Interval interval;
  bool restart_on_abort;
} PomodoroInterval;

// Initializes an interval to the number of minutes and seconds remaining and
// sets the restart-on-abort flag.

void pomodoro_interval_init(PomodoroInterval* interval, unsigned int minutes,
  unsigned int seconds, bool restart_on_abort);
