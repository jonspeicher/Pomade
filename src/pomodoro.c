// ----------------------------------------------------------------------------
// pomodoro - Defines a model to track progress through the pomodoro technique
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <stdbool.h>

#include "interval.h"
#include "pomodoro.h"
#include "pomodoro_config.h"

// Define a type used to represent the initial state of a pomodoro segment.

typedef struct {
  PomodoroSegmentType type;
  unsigned int minutes;
  unsigned int seconds;
  bool restart_on_abort;
} PomodoroSegmentConfig;

// Define the configuration of the various pomodoro technique segments. This
// table must be in the same order as the pomodoro segment type enum.

static const PomodoroSegmentConfig POMODORO_SEGMENT_CONFIG_TABLE[] = {
  {POMODORO_SEGMENT_TYPE_POMODORO, POMODORO_MINUTES, POMODORO_SECONDS, true},
  {POMODORO_SEGMENT_TYPE_BREAK, SHORT_BREAK_MINUTES, SHORT_BREAK_SECONDS, false},
  {POMODORO_SEGMENT_TYPE_BREAK, LONG_BREAK_MINUTES, LONG_BREAK_SECONDS, false}
};

// Private functions.

void segment_init(PomodoroSegment* segment, PomodoroSegmentConfig config);
void set_this_segment(Pomodoro* pomodoro, unsigned int index);

// Public functions -----------------------------------------------------------

void pomodoro_init(Pomodoro* pomodoro) {
  for (unsigned int i = 0; i < POMODORO_SEGMENT_INDEX_COUNT; i++) {
    segment_init(&pomodoro->segments[i], POMODORO_SEGMENT_CONFIG_TABLE[i]);
  }
  set_this_segment(pomodoro, POMODORO_SEGMENT_INDEX_POMODORO);
  pomodoro->pomodoros_completed = 0;
}

void pomodoro_start_segment(Pomodoro* pomodoro) {
  if (pomodoro->pomodoros_completed >= POMODORO_COUNT_FOR_LONG_BREAK) {
    pomodoro->pomodoros_completed = 0;
  }
}

void pomodoro_complete_segment(Pomodoro* pomodoro) {
  if (pomodoro->this_segment->type == POMODORO_SEGMENT_TYPE_BREAK) {
    set_this_segment(pomodoro, POMODORO_SEGMENT_INDEX_POMODORO);
  } else if (++pomodoro->pomodoros_completed >= POMODORO_COUNT_FOR_LONG_BREAK) {
    set_this_segment(pomodoro, POMODORO_SEGMENT_INDEX_LONG_BREAK);
  } else {
    set_this_segment(pomodoro, POMODORO_SEGMENT_INDEX_SHORT_BREAK);
  }
}

void pomodoro_abort_segment(Pomodoro* pomodoro) {
  if (pomodoro->this_segment->type == POMODORO_SEGMENT_TYPE_BREAK) {
    set_this_segment(pomodoro, POMODORO_SEGMENT_INDEX_POMODORO);
  }
}

// Private functions ----------------------------------------------------------

void segment_init(PomodoroSegment* segment, PomodoroSegmentConfig config) {
  interval_init(&segment->interval, config.minutes, config.seconds);
  segment->type = config.type;
  segment->restart_on_abort = config.restart_on_abort;
}

void set_this_segment(Pomodoro* pomodoro, unsigned int index) {
  pomodoro->this_segment_index = index;
  pomodoro->this_segment = &pomodoro->segments[index];
}
