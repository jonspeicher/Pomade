// ----------------------------------------------------------------------------
// segment_view - Displays the current pomodoro technique segment type and data
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include <pebble_fonts.h>

#include "segment_view.h"

// Define the various user interface elements comprising this view.

static TextLayer segment_type_text_layer;
static Layer pomodoro_count_layer;

// Define a variable to hold the previous unload handler for chaining.

static WindowHandler previous_unload_handler;

// Private functions.

static void load_and_add_view(Window* window);
static void remove_and_unload_view(Window* window);

// Public functions -----------------------------------------------------------

void segment_view_init(Window* window) {
  load_and_add_view(window);
  previous_unload_handler = window->window_handlers.unload;
  window_set_window_handlers(window, (WindowHandlers) {
    .unload = remove_and_unload_view
  });
}

void segment_view_show_segment_type(PomodoroSegmentType type) {
  // TBD: Make this a lookup table - JRS 8/30
  if (type == POMODORO_SEGMENT_TYPE_POMODORO) {
    text_layer_set_text(&segment_type_text_layer, "pomodoro");
  } else if (type == POMODORO_SEGMENT_TYPE_BREAK) {
    text_layer_set_text(&segment_type_text_layer, "break");
  }
}

// Private functions ----------------------------------------------------------

void update_pomodoro_count_layer(Layer* layer, GContext* ctx) {
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_circle(ctx, GPoint(20, 20), 5);
}

void load_and_add_view(Window* window) {
  // TBD: Is there a nicer way to do this? - JRS 8/16
  text_layer_init(&segment_type_text_layer, GRect(0, 90,
    window->layer.frame.size.w - ACTION_BAR_WIDTH, 40));
  text_layer_set_text_alignment(&segment_type_text_layer, GTextAlignmentCenter);
  text_layer_set_font(&segment_type_text_layer,
    fonts_get_system_font(FONT_KEY_GOTHIC_28));
  layer_add_child(&window->layer, &segment_type_text_layer.layer);

  layer_init(&pomodoro_count_layer, GRect(0, 50,
    window->layer.frame.size.w - ACTION_BAR_WIDTH, 40));
  layer_set_update_proc(&pomodoro_count_layer, update_pomodoro_count_layer);
  layer_add_child(&window->layer, &pomodoro_count_layer);
}

void remove_and_unload_view(Window* window) {
  layer_remove_from_parent(&segment_type_text_layer.layer);
  if (previous_unload_handler) {
    previous_unload_handler(window);
  }
}
