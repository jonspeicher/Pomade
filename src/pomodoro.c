// ----------------------------------------------------------------------------
// pomodoro - Defines a model to track progress through the Pomodoro Technique
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include "pomodoro.h"
#include "pomodoro_config.h"
#include "pomodoro_interval.h"

void pomodoro_init(Pomodoro* pomodoro) {
  pomodoro_interval_init(&pomodoro->pomodoro, POMODORO_MINUTES, POMODORO_SECONDS, true);
  pomodoro_interval_init(&pomodoro->rest, REST_MINUTES, REST_SECONDS, false);
  pomodoro->this_segment = &pomodoro->pomodoro;
}

void pomodoro_complete_segment(Pomodoro* pomodoro) {
  pomodoro->this_segment = (pomodoro->this_segment == &pomodoro->pomodoro) ?
    &pomodoro->rest: &pomodoro->pomodoro;
}

void pomodoro_abort_segment(Pomodoro* pomodoro) {
  if (pomodoro->this_segment == &pomodoro->rest) {
    pomodoro->this_segment = &pomodoro->pomodoro;
  }
}
