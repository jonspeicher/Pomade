// ----------------------------------------------------------------------------
// action_window - Initializes and displays the action window
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Defines a type to represent an action window. Note that the Window element
// *must* appear first in this struct to allow pointers to the struct to be
// cast to pointers to Window for Pebble SDK function call compatibility.

typedef struct {
  Window window;
} ActionWindow;

// Initializes the window. This will load any necessary resources and lay the
// window out, but will not display the window.

void action_window_init(ActionWindow* window, char* debug_name);

// Sets the click config provider for the window, which will be invoked
// whenever the window needs to update the click configuration.

void action_window_set_click_config_provider(ClickConfigProvider provider);

// Returns the usable width of the action window's root layer.

unsigned int action_window_get_width(ActionWindow* window);

// Sets the icon for the given button on the action bar to the bitmap provided.

void action_window_set_action_bar_icon(ButtonId button_id, GBitmap* icon);

// Clears all the icons from the action bar. This should be called prior to
// deinitialization of the icons by their owner.

void action_window_clear_action_bar_icons();
