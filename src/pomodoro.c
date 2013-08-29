// ----------------------------------------------------------------------------
// pomodoro - Defines a model to track progress through the Pomodoro Technique
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include "interval.h"
#include "pomodoro.h"
#include "pomodoro_config.h"

void pomodoro_init(Pomodoro* pomodoro) {
  interval_init(&pomodoro->segments[POMODORO_SEGMENT_TYPE_POMODORO].interval, POMODORO_MINUTES, POMODORO_SECONDS);
  // TBD: I'm not sure I like this; could be derived from seg type in a
  // "getter method" - JRS 8/29
  pomodoro->segments[POMODORO_SEGMENT_TYPE_POMODORO].type = POMODORO_SEGMENT_TYPE_POMODORO;
  pomodoro->segments[POMODORO_SEGMENT_TYPE_POMODORO].restart_on_abort = true;

  interval_init(&pomodoro->segments[POMODORO_SEGMENT_TYPE_BREAK].interval, REST_MINUTES, REST_SECONDS);
  pomodoro->segments[POMODORO_SEGMENT_TYPE_BREAK].type = POMODORO_SEGMENT_TYPE_BREAK;
  pomodoro->segments[POMODORO_SEGMENT_TYPE_BREAK].restart_on_abort = false;

  pomodoro->this_segment = &pomodoro->segments[POMODORO_SEGMENT_TYPE_POMODORO];
}

void pomodoro_complete_segment(Pomodoro* pomodoro) {
  pomodoro->this_segment = (pomodoro->this_segment->type == POMODORO_SEGMENT_TYPE_POMODORO) ?
    &pomodoro->segments[POMODORO_SEGMENT_TYPE_BREAK] : &pomodoro->segments[POMODORO_SEGMENT_TYPE_POMODORO];
}

void pomodoro_abort_segment(Pomodoro* pomodoro) {
  if (pomodoro->this_segment->type == POMODORO_SEGMENT_TYPE_BREAK) {
    pomodoro->this_segment = &pomodoro->segments[POMODORO_SEGMENT_TYPE_POMODORO];
  }
}
