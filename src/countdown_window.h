// ----------------------------------------------------------------------------
// TBD - TBD
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

void timer_window_init();
void timer_window_push();
void timer_window_set_time_remaining(char* time_remaining);
void timer_window_show_abort();
void timer_window_show_restart();
void timer_window_set_click_config_provider(ClickConfigProvider click_config_provider);
