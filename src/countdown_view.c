// ----------------------------------------------------------------------------
// countdown_view - Displays a countdown timer and controls
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include <pebble_app.h>
#include <pebble_fonts.h>

#include "action_window.h"
#include "countdown_view.h"

// Define the length in characters of the countdown string, including the NULL.

#define COUNTDOWN_STRING_LENGTH 6

// Define the format for the countdown string.

#define COUNTDOWN_STRING_FORMAT "%d:%02d"

// Define the countdown string. The API requires that this not be stack-based.

static char countdown_string[COUNTDOWN_STRING_LENGTH] = "";

// Define the various user interface elements comprising this view.

static ActionWindow* action_window;
static TextLayer countdown_text_layer;

// Define a structure to hold the window's bitmaps in a convenient aggregate.

static struct {
  HeapBitmap start;
  HeapBitmap restart;
  HeapBitmap abort;
} icons;

// Define a variable to hold the previous unload handler for chaining.

static WindowHandler previous_unload_handler;

// Private functions.

static void load_and_add_view(Window* window, unsigned int width);
static void remove_and_unload_view(Window* window);

// Public functions -----------------------------------------------------------

// TBD: Some of the ActionWindow parameters, especially in the headers, could
// and should be called action_window for clarity - JRS 9/25

void countdown_view_init(ActionWindow* window, ClickConfigProvider provider) {
  action_window = window;

  previous_unload_handler = action_window->window.window_handlers.unload;
  window_set_window_handlers(&action_window->window, (WindowHandlers) {
    .unload = remove_and_unload_view
  });
  action_window_set_click_config_provider(action_window, provider);

  unsigned int width = action_window_get_width(action_window);
  load_and_add_view(&action_window->window, width);
  countdown_view_show_start();
}

void countdown_view_set_time_remaining_sec(unsigned int seconds) {
  unsigned int minutes_left = seconds / 60;
  unsigned int seconds_left = seconds % 60;

  snprintf(countdown_string, COUNTDOWN_STRING_LENGTH, COUNTDOWN_STRING_FORMAT,
    minutes_left, seconds_left);
  text_layer_set_text(&countdown_text_layer, countdown_string);
}

void countdown_view_show_start() {
  action_window_set_icon(action_window, BUTTON_ID_SELECT, &icons.start.bmp);
}

void countdown_view_show_restart() {
  action_window_set_icon(action_window, BUTTON_ID_SELECT, &icons.restart.bmp);
}

void countdown_view_show_abort() {
  action_window_set_icon(action_window, BUTTON_ID_SELECT, &icons.abort.bmp);
}

// Private functions ----------------------------------------------------------

void load_and_add_view(Window* window, unsigned int width) {
  heap_bitmap_init(&icons.start, RESOURCE_ID_ICON_START);
  heap_bitmap_init(&icons.restart, RESOURCE_ID_ICON_RESTART);
  heap_bitmap_init(&icons.abort, RESOURCE_ID_ICON_ABORT);

  GRect text_layer_frame = GRect(0, 20, width, 55);
  text_layer_init(&countdown_text_layer, text_layer_frame);
  text_layer_set_text_alignment(&countdown_text_layer, GTextAlignmentCenter);
  text_layer_set_font(&countdown_text_layer,
    fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  layer_add_child(&window->layer, &countdown_text_layer.layer);
}

void remove_and_unload_view(Window* window) {
  layer_remove_from_parent(&countdown_text_layer.layer);

  action_window_clear_icons(action_window);
  heap_bitmap_deinit(&icons.start);
  heap_bitmap_deinit(&icons.restart);
  heap_bitmap_deinit(&icons.abort);

  if (previous_unload_handler) {
    previous_unload_handler(window);
  }
}
