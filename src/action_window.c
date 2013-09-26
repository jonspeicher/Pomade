// ----------------------------------------------------------------------------
// action_window - Initializes and displays the action window
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

// TBD: The z-order bug is back; fix it this time by adding layers to this
// window via a specific method that puts them below the action bar - JRS 9/24

#include <pebble_os.h>

// Define the various user interface elements comprising this window.

static ActionBarLayer action_bar;

// Private functions.

static void window_unload(Window* window);

// Public functions -----------------------------------------------------------

void action_window_init(Window* window, char* debug_name) {
  window_init(window, debug_name);
  action_bar_layer_init(&action_bar);
  action_bar_layer_add_to_window(&action_bar, window);
  window_set_window_handlers(window, (WindowHandlers) {
    .unload = window_unload
  });
}

// TBD: Split into multiple callbacks, one per button, figure what to pass from
// where and how to register (e.g. what the handler registration process looks
// like), who owns the actual CCP (I believe I decided that it would be this
// window), and how other controllers (e.g. stat display) get access to this
// one window (e.g. which controller "owns" this window; Pomade?) - JRS 9/24

void action_window_set_click_config_provider(ClickConfigProvider provider) {
  action_bar_layer_set_click_config_provider(&action_bar, provider);
}

void action_window_push(Window* window) {
  window_stack_push(window, true);
}

unsigned int action_window_get_width(Window* window) {
  Layer* layer = window_get_root_layer(window);
  GRect frame = layer_get_frame(layer);
  return frame.size.w - ACTION_BAR_WIDTH;
}

void action_window_set_action_bar_icon(ButtonId button_id, GBitmap* icon) {
  action_bar_layer_set_icon(&action_bar, button_id, icon);
}

void action_window_clear_action_bar_icons() {
  action_bar_layer_clear_icon(&action_bar, BUTTON_ID_UP);
  action_bar_layer_clear_icon(&action_bar, BUTTON_ID_SELECT);
  action_bar_layer_clear_icon(&action_bar, BUTTON_ID_DOWN);
}

// Private functions ----------------------------------------------------------

void window_unload(Window* window) {
  action_bar_layer_remove_from_window(&action_bar);
}
