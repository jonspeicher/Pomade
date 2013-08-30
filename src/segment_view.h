// ----------------------------------------------------------------------------
// segment_view - Displays the current pomodoro technique segment type and data
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>
#include "pomodoro.h"    // TBD: I'm not sure I like this - JRS 8/30

// Creates the segment view and adds it to the window specified.

void segment_view_init(Window* window);

// Shows the specified segment type.

void segment_view_show_segment_type(PomodoroSegmentType type);
