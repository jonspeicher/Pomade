// ----------------------------------------------------------------------------
// pomodoro - Defines a model to track progress through the pomodoro technique
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <stdbool.h>
#include "interval.h"

// Defines a type to hold the various pomodoro technique segment types.

typedef enum {
  POMODORO_SEGMENT_TYPE_POMODORO = 0,
  POMODORO_SEGMENT_TYPE_BREAK,
  POMODORO_SEGMENT_TYPE_COUNT
} PomodoroSegmentType;

// Defines a type to hold a pomodoro technique segment.

// TBD: This should probably be an opaque struct at this point - JRS 9/1

typedef struct {
  PomodoroSegmentType type;
  Interval interval;
  bool restart_on_abort;
} PomodoroSegment;

// Defines a type to hold the indexes of the pomodoro technique segments.

typedef enum {
  POMODORO_SEGMENT_INDEX_POMODORO = 0,
  POMODORO_SEGMENT_INDEX_SHORT_BREAK,
  POMODORO_SEGMENT_INDEX_LONG_BREAK,
  POMODORO_SEGMENT_INDEX_COUNT
} PomodoroSegmentIndex;

// Defines a type to hold the pomodoro technique segment sequence.

typedef struct {
  unsigned int this_segment_index;
  PomodoroSegment* this_segment;
  PomodoroSegment segments[POMODORO_SEGMENT_INDEX_COUNT];
} Pomodoro;

// Initializes the pomodoro technique sequence structure.

void pomodoro_init(Pomodoro* pomodoro);

// Completes the current pomodoro technique segment and causes an advance to
// the next appropriate segment in the pomodoro technique sequence.

void pomodoro_complete_segment(Pomodoro* pomodoro);

// Aborts the current pomodoro tecnique segment and causes an advance to the
// next appropriate segment in the pomodoro technique sequence.

void pomodoro_abort_segment(Pomodoro* pomodoro);
