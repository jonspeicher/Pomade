// ----------------------------------------------------------------------------
// segment_view - Displays the current pomodoro technique segment type and data
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include <pebble_fonts.h>

#include "segment_view.h"

// Define a variable to hold the number of pomodoro indicators on the view.

static unsigned int num_pomodoro_indicators;

// Define a variable to hold the count of pomodoros completed.

static unsigned int pomodoros_completed;

// Define the various user interface elements comprising this view.

static TextLayer break_layer;
static Layer pomodoro_layer;

// Define a variable to hold the previous unload handler for chaining.

static WindowHandler previous_unload_handler;

// Private functions.

static void load_and_add_view(Window* window);
static void remove_and_unload_view(Window* window);
static void update_pomodoro_layer(Layer* layer, GContext* ctx);

// Public functions -----------------------------------------------------------

void segment_view_init(Window* window) {
  load_and_add_view(window);
  previous_unload_handler = window->window_handlers.unload;
  window_set_window_handlers(window, (WindowHandlers) {
    .unload = remove_and_unload_view
  });
}

void segment_view_set_num_pomodoro_indicators(unsigned int num_indicators) {
  num_pomodoro_indicators = num_indicators;
}

void segment_view_set_pomodoros_completed(unsigned int completed) {
  pomodoros_completed = completed;
}

void segment_view_show_segment_type(PomodoroSegmentType type) {
  // TBD: This would be the place to kick off flyout animation - JRS 9/4
  layer_set_hidden(&break_layer.layer, (type != POMODORO_SEGMENT_TYPE_BREAK));
  layer_set_hidden(&pomodoro_layer, (type != POMODORO_SEGMENT_TYPE_POMODORO));
}

// Private functions ----------------------------------------------------------

void load_and_add_view(Window* window) {
  unsigned int width = window->layer.frame.size.w - ACTION_BAR_WIDTH;

  layer_init(&pomodoro_layer, GRect(0, 90, width, 40));
  layer_set_update_proc(&pomodoro_layer, update_pomodoro_layer);
  layer_add_child(&window->layer, &pomodoro_layer);

  text_layer_init(&break_layer, GRect(0, 90, width, 40));
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

void update_pomodoro_layer(Layer* layer, GContext* ctx) {
  unsigned int span = layer->frame.size.w / (num_pomodoro_indicators + 1);
  unsigned int radius = 5;
  GPoint center = GPoint(span, 20);

  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_fill_color(ctx, GColorBlack);

  for (unsigned int i = 0; i < num_pomodoro_indicators; i++) {
    center.x = span * (i + 1);
    if (i < pomodoros_completed) {
      graphics_fill_circle(ctx, center, radius);
    } else {
      graphics_draw_circle(ctx, center, radius);
    }
  }
}
