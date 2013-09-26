// ----------------------------------------------------------------------------
// segment_view - Displays the current pomodoro technique segment type and data
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>
#include "pomodoro.h"    // TBD: I'm not sure I like this - JRS 8/30

// Creates the segment view with the specified width and adds it to the window
// specified.

void segment_view_init(Window* window, unsigned int width);

// Sets the number of pomodoro indicators that will appear on the view.

void segment_view_set_num_pomodoro_indicators(unsigned int num_indicators);

// Sets the number of pomodoros that have been completed in this sequence.

void segment_view_set_pomodoros_completed(unsigned int pomodoros_completed);

// Shows the specified segment type.

void segment_view_show_segment_type(PomodoroSegmentType type);
