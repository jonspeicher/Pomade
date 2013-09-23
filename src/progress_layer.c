// ----------------------------------------------------------------------------
// progress_layer - Displays a configurable progress bar
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include "progress_layer.h"

// Define a variable to hold the number of steps indicated by the layer.

static unsigned int num_steps;

// Define a variable to hold the number of steps completed.

static unsigned int steps_completed;

// Private functions.

static void update_progress_layer(Layer* layer, GContext* ctx);

// Public functions -----------------------------------------------------------

void progress_layer_init(Layer* layer, GRect rect) {
  layer_init(layer, rect);
  layer_set_update_proc(layer, update_progress_layer);
}

void progress_layer_set_num_steps(Layer* layer, unsigned int steps) {
  num_steps = steps;
}

void progress_layer_set_num_steps_completed(Layer* layer, unsigned int steps) {
  if (steps > num_steps) steps = num_steps;
  steps_completed = steps;
}

// Private functions ----------------------------------------------------------

void update_progress_layer(Layer* layer, GContext* ctx) {
  GRect frame = layer_get_frame(layer);
  unsigned int span = frame.size.w / (num_steps + 1);
  unsigned int radius = 5;
  GPoint center = GPoint(span, 20);

  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_fill_color(ctx, GColorBlack);

  for (unsigned int i = 0; i < num_steps; i++) {
    center.x = span * (i + 1);
    if (i < steps_completed) {
      graphics_fill_circle(ctx, center, radius);
    } else {
      graphics_draw_circle(ctx, center, radius);
    }
  }
}
