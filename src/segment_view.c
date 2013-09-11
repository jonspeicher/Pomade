// ----------------------------------------------------------------------------
// segment_view - Displays the current pomodoro technique segment type and data
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include <pebble_fonts.h>

#include "flyout_animation.h"
#include "pomodoro.h"
#include "progress_layer.h"
#include "segment_view.h"

// Define a variable to hold the currently-displayed segment type.

static PomodoroSegmentType current_segment_type;

// Define the various user interface elements comprising this view.

static TextLayer break_layer;
static Layer pomodoro_layer;
static FlyoutAnimation flyout_animation;

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
  if (type == current_segment_type) return;
  current_segment_type = type;
  flyout_animation_swap_layers(&flyout_animation);
  flyout_animation_schedule(&flyout_animation);
}

// Private functions ----------------------------------------------------------

void load_and_add_view(Window* window) {
  unsigned int width = window->layer.frame.size.w - ACTION_BAR_WIDTH;
  GRect rect = GRect(0, 90, width, 40);

  progress_layer_init(&pomodoro_layer, rect);

  text_layer_init(&break_layer, rect);
  text_layer_set_text_alignment(&break_layer, GTextAlignmentCenter);
  text_layer_set_font(&break_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text(&break_layer, "break");

  flyout_animation_init(&flyout_animation, &pomodoro_layer, &break_layer.layer);
  flyout_animation_add_child(&window->layer, &flyout_animation);
}

void remove_and_unload_view(Window* window) {
  layer_remove_from_parent(&pomodoro_layer);
  layer_remove_from_parent(&break_layer.layer);
  if (previous_unload_handler) {
    previous_unload_handler(window);
  }
}
