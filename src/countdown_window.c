// ----------------------------------------------------------------------------
// TBD - TBD
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include <pebble_app.h>
#include <pebble_fonts.h>

// TBD

static Window timer_window;
static TextLayer countdown_layer;
static ActionBarLayer action_bar;

static struct {
  HeapBitmap start;
  HeapBitmap restart;
  HeapBitmap abort;
} icons;

// Private functions.

static void window_layout(Window* window);
static void window_unload(Window* window);

// Public functions -----------------------------------------------------------

void timer_window_init() {
  window_init(&timer_window, "Pomade");
  window_set_window_handlers(&timer_window, (WindowHandlers) {
    .unload = window_unload
  });
  window_layout(&timer_window);
}

void timer_window_push() {
  window_stack_push(&timer_window, true);
}

void timer_window_set_click_config_provider(ClickConfigProvider click_config_provider) {
  action_bar_layer_set_click_config_provider(&action_bar, click_config_provider);
}

void timer_window_set_time_remaining(char* time_remaining) {
  text_layer_set_text(&countdown_layer, time_remaining);
}

void timer_window_show_abort() {
  action_bar_layer_set_icon(&action_bar, BUTTON_ID_SELECT, &icons.abort.bmp);
}

void timer_window_show_restart() {
  action_bar_layer_set_icon(&action_bar, BUTTON_ID_SELECT, &icons.restart.bmp);
}

// Private functions ----------------------------------------------------------

void window_layout(Window* window) {
  heap_bitmap_init(&icons.start, RESOURCE_ID_ICON_START);
  heap_bitmap_init(&icons.restart, RESOURCE_ID_ICON_RESTART);
  heap_bitmap_init(&icons.abort, RESOURCE_ID_ICON_ABORT);

  action_bar_layer_init(&action_bar);
  action_bar_layer_set_icon(&action_bar, BUTTON_ID_SELECT, &icons.start.bmp);
  action_bar_layer_add_to_window(&action_bar, window);

  text_layer_init(&countdown_layer,
    GRect(0, 10, window->layer.frame.size.w - ACTION_BAR_WIDTH, window->layer.frame.size.h));
  text_layer_set_text_alignment(&countdown_layer, GTextAlignmentCenter);
  text_layer_set_font(&countdown_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  layer_add_child(&window->layer, &countdown_layer.layer);
}

void window_unload(Window* window) {
  action_bar_layer_remove_from_window(&action_bar);
  heap_bitmap_deinit(&icons.start);
  heap_bitmap_deinit(&icons.restart);
  heap_bitmap_deinit(&icons.abort);
}
