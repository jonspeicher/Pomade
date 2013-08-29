// ----------------------------------------------------------------------------
// pomodoro - Defines a model to track progress through the Pomodoro Technique
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include "interval.h"
#include "pomodoro.h"
#include "pomodoro_config.h"

void pomodoro_init(Pomodoro* pomodoro) {
  interval_init(&pomodoro->pomodoro.interval, POMODORO_MINUTES, POMODORO_SECONDS);
  pomodoro->pomodoro.restart_on_abort = true;

  interval_init(&pomodoro->rest.interval, REST_MINUTES, REST_SECONDS);
  pomodoro->rest.restart_on_abort = false;

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
