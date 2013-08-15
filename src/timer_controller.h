#pragma once

#include <pebble_os.h>

#define TIMER_CONTROLLER_COOKIE 1

void timer_controller_init(AppContextRef ctx);
void timer_controller_periodic_event(AppTimerHandle handle);
