#include <pebble_os.h>

#include "pomodoro.h"
#include "timer_controller.h"
#include "timer_window.h"

static Pomodoro pomodoro;

#define POMODORO_TICK_PERIOD_SEC 1
#define POMODORO_TICK_PERIOD_MS  POMODORO_TICK_PERIOD_SEC * 1000

static AppContextRef application_context;
static AppTimerHandle timer;

void select_clicked(ClickRecognizerRef recognizer, void* context) {
  if (pomodoro.running) {
    app_timer_cancel_event(application_context, timer);
    pomodoro_abort(&pomodoro);
    vibes_double_pulse();
    timer_window_show_restart();
  } else {
    timer = app_timer_send_event(application_context, POMODORO_TICK_PERIOD_MS, TIMER_CONTROLLER_COOKIE);
    pomodoro_init(&pomodoro);
    timer_window_set_time_remaining(pomodoro.time_left_string);
    pomodoro_start(&pomodoro);
    timer_window_show_abort();
  }
}

void click_config_provider(ClickConfig **config, void* context) {
  config[BUTTON_ID_SELECT]->click.handler = select_clicked;
}

void timer_controller_init(AppContextRef ctx) {
  application_context = ctx;
  pomodoro_init(&pomodoro);
  timer_window_init();
  timer_window_set_time_remaining(pomodoro.time_left_string);
  timer_window_set_click_config_provider(click_config_provider);
  timer_window_push();
}

// This needs some changing
void timer_controller_periodic_event(AppTimerHandle handle) {
  timer = handle;
  pomodoro_decrement_by_seconds(&pomodoro, POMODORO_TICK_PERIOD_SEC);
  timer_window_set_time_remaining(pomodoro.time_left_string);

  if (pomodoro.complete) {
    vibes_long_pulse();
  } else {
    timer = app_timer_send_event(application_context, POMODORO_TICK_PERIOD_MS, TIMER_CONTROLLER_COOKIE);
  }
}
