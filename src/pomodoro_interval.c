// ----------------------------------------------------------------------------
// pomodoro_interval - Provides intervals specific to the Pomodoro Technique
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <stdbool.h>

#include "interval.h"
#include "pomodoro_interval.h"

void pomodoro_interval_init(PomodoroInterval* interval, unsigned int minutes,
  unsigned int seconds, bool restart_on_abort) {
  interval_init(&interval->interval, minutes, seconds);
  interval->restart_on_abort = restart_on_abort;
}
