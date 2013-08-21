// ----------------------------------------------------------------------------
// countdown_controller - Controls arbitrary interval countdown and display
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>

#include "cookies.h"
#include "countdown_controller.h"
#include "countdown_view.h"
#include "interval.h"

// Define the duration of each tick to be used when counting down.

#define COUNTDOWN_TICK_SEC 1
#define COUNTDOWN_TICK_MS  COUNTDOWN_TICK_SEC * 1000

// Define the data structure used to manage the countdown interval.

static Interval* interval;

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

void countdown_controller_init(AppContextRef ctx, Window* window) {
  app_ctx = ctx;
  countdown_view_init(window, click_config_provider);
}

void countdown_controller_set_interval(Interval* new_interval) {
  interval = new_interval;
  countdown_view_set_time_remaining_sec(interval->time_remaining_sec);
}

// Event handlers -------------------------------------------------------------

// TBD: It's probably going to be necessary to pull these up a level and/or
// hook up some callbacks between this controller and the coordinating
// controller - JRS 8/20

void click_config_provider(ClickConfig* config[], void* ctx) {
  config[BUTTON_ID_SELECT]->click.handler = toggle_countdown_state_click;
}

void toggle_countdown_state_click(ClickRecognizerRef recog, void* ctx) {
  if (interval->running) {
    cancel_countdown_tick_timer();
    interval_abort(interval);
    vibes_double_pulse();
    countdown_view_show_restart();
  } else {
    interval_reset(interval);
    countdown_view_set_time_remaining_sec(interval->time_remaining_sec);
    countdown_view_show_abort();
    interval_start(interval);
    start_countdown_tick_timer();
  }
}

void countdown_controller_timer_event(AppTimerHandle handle) {
  if (interval->running) {
    interval_decrement_by_seconds(interval, COUNTDOWN_TICK_SEC);
    countdown_view_set_time_remaining_sec(interval->time_remaining_sec);
  }

  if (interval->complete) {
    vibes_long_pulse();
  } else {
    // TBD: Account for drift here if there's a clean way to do it - JRS 8/19
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
