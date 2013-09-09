// ----------------------------------------------------------------------------
// segment_view - Displays the current pomodoro technique segment type and data
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include <pebble_fonts.h>

#include "pomodoro.h"
#include "progress_layer.h"
#include "segment_view.h"

// Define a variable to hold the currently-displayed segment type.

static PomodoroSegmentType current_segment_type;

// Define the various user interface elements comprising this view.

static TextLayer break_layer;
static Layer pomodoro_layer;

static PropertyAnimation flyout, flyin;
static GRect left_rect, center_rect, right_rect;

// Define a variable to hold the previous unload handler for chaining.

static WindowHandler previous_unload_handler;

// Private functions.

static void load_and_add_view(Window* window);
static void remove_and_unload_view(Window* window);

// Public functions -----------------------------------------------------------

void segment_view_init(Window* window) {
  current_segment_type = POMODORO_SEGMENT_TYPE_POMODORO;
  load_and_add_view(window);
  previous_unload_handler = window->window_handlers.unload;
  window_set_window_handlers(window, (WindowHandlers) {
    .unload = remove_and_unload_view
  });
}

void segment_view_set_num_pomodoro_indicators(unsigned int num_indicators) {
  progress_layer_set_num_steps(&pomodoro_layer, num_indicators);
}

void segment_view_set_pomodoros_completed(unsigned int pomodoros_completed) {
  progress_layer_set_num_steps_completed(&pomodoro_layer, pomodoros_completed);
}

void segment_view_show_segment_type(PomodoroSegmentType type) {
  Layer* in;
  Layer* out;

  if (type == current_segment_type) return;
  current_segment_type = type;

  if (type == POMODORO_SEGMENT_TYPE_POMODORO) {
    in = &pomodoro_layer;
    out = &break_layer.layer;
  } else {
    in = &break_layer.layer;
    out = &pomodoro_layer;
  }

  property_animation_init_layer_frame(&flyout, out, &center_rect, &left_rect);
  property_animation_init_layer_frame(&flyin, in, &right_rect, &center_rect);

  animation_schedule(&flyout.animation);
  animation_schedule(&flyin.animation);
}

// Private functions ----------------------------------------------------------

void load_and_add_view(Window* window) {
  unsigned int width = window->layer.frame.size.w - ACTION_BAR_WIDTH;

  left_rect = GRect(-width, 90, width, 40);
  center_rect = GRect(0, 90, width, 40);
  right_rect = GRect(width, 90, width ,40);

  animation_set_curve(&flyout.animation, AnimationCurveEaseInOut);
  animation_set_curve(&flyin.animation, AnimationCurveEaseInOut);

  progress_layer_init(&pomodoro_layer, center_rect);
  layer_add_child(&window->layer, &pomodoro_layer);

  text_layer_init(&break_layer, right_rect);
  text_layer_set_text_alignment(&break_layer, GTextAlignmentCenter);
  text_layer_set_font(&break_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text(&break_layer, "break");
  layer_add_child(&window->layer, &break_layer.layer);
}

void remove_and_unload_view(Window* window) {
  layer_remove_from_parent(&pomodoro_layer);
  layer_remove_from_parent(&break_layer.layer);
  if (previous_unload_handler) {
    previous_unload_handler(window);
  }
}
