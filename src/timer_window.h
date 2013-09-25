// ----------------------------------------------------------------------------
// timer_window - Initializes and displays the main timer window
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Initializes the timer window. This will load any necessary resources and lay
// the window out, but will not display the window.

void timer_window_init(Window* window);

// Sets the click config provider for the window, which will be invoked
// whenever the window needs to update the click configuration.

void timer_window_set_click_config_provider(ClickConfigProvider provider);

// Pushes the timer window onto the window stack.

void timer_window_push(Window* window);

// Sets the icon for the given button on the action bar to the bitmap provided.

void timer_window_set_action_bar_icon(ButtonId button_id, GBitmap* icon);

// Clears all the icons from the action bar. This should be called prior to
// deinitialization of the icons by their owner.

void timer_window_clear_action_bar_icons();
