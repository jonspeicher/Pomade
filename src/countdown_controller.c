// ----------------------------------------------------------------------------
// countdown_controller - Controls arbitrary interval countdown and display
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

#include "cookies.h"
#include "countdown_controller.h"
#include "countdown_window.h"
#include "interval.h"

// Define the duration of each tick to be used when counting down.

#define COUNTDOWN_TICK_SEC 1
#define COUNTDOWN_TICK_MS  COUNTDOWN_TICK_SEC * 1000

// Define the data structure used to manage the countdown interval.

static Interval interval;

// Define the persistent handles necessary for interacting with the Pebble API.

static AppContextRef app_ctx;
static AppTimerHandle timer;

// Event handlers.

static void click_config_provider(ClickConfig* config[], void* ctx);
static void toggle_countdown_state_click(ClickRecognizerRef recog, void* ctx);

// Private functions.

static void start_countdown_tick_timer();
static void cancel_countdown_tick_timer();

// Public functions -----------------------------------------------------------

void countdown_controller_init(AppContextRef ctx) {
  app_ctx = ctx;
  interval_init(&interval, 25, 0);
  countdown_window_init(click_config_provider);
  countdown_window_set_time_remaining(interval.time_remaining_string);
  countdown_window_push();
}

// Event handlers -------------------------------------------------------------

void click_config_provider(ClickConfig* config[], void* ctx) {
  config[BUTTON_ID_SELECT]->click.handler = toggle_countdown_state_click;
}

void toggle_countdown_state_click(ClickRecognizerRef recog, void* ctx) {
  if (interval.running) {
    cancel_countdown_tick_timer();
    interval_abort(&interval);
    vibes_double_pulse();
    countdown_window_show_restart();
  } else {
    interval_reset(&interval);
    countdown_window_set_time_remaining(interval.time_remaining_string);
    countdown_window_show_abort();
    interval_start(&interval);
    start_countdown_tick_timer();
  }
}

void countdown_controller_timer_event(AppTimerHandle handle) {
  interval_decrement_by_seconds(&interval, COUNTDOWN_TICK_SEC);
  countdown_window_set_time_remaining(interval.time_remaining_string);

  if (interval.complete) {
    vibes_long_pulse();
  } else {
    start_countdown_tick_timer();
  }
}

// Private functions ----------------------------------------------------------

void start_countdown_tick_timer() {
  timer = app_timer_send_event(app_ctx, COUNTDOWN_TICK_MS, COUNTDOWN_COOKIE);
}

void cancel_countdown_tick_timer() {
  app_timer_cancel_event(app_ctx, timer);
}
