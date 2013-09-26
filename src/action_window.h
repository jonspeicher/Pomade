// ----------------------------------------------------------------------------
// action_window - Initializes and displays the action window
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Initializes the window. This will load any necessary resources and lay the
// window out, but will not display the window.

void action_window_init(Window* window, char* debug_name);

// Sets the click config provider for the window, which will be invoked
// whenever the window needs to update the click configuration.

void action_window_set_click_config_provider(ClickConfigProvider provider);

// Pushes the window onto the window stack.

void action_window_push(Window* window);

// Returns the usable width of the action window's root layer.

unsigned int action_window_get_width(Window* window);

// Sets the icon for the given button on the action bar to the bitmap provided.

void action_window_set_action_bar_icon(ButtonId button_id, GBitmap* icon);

// Clears all the icons from the action bar. This should be called prior to
// deinitialization of the icons by their owner.

void action_window_clear_action_bar_icons();
