// TBD: app is the controller, owns timer and click handlers (which are registered
// via the view), view is the window/layer/etc, model is pomodoro
// controller makes decisions based on model and input coming called back from
// the view, then updates the model and updates the view with the model

#include <pebble_os.h>
#include <pebble_app.h>
#include <pebble_fonts.h>

#include "pomodoro.h"
#include "timer_window.h"

#define MY_UUID { 0x78, 0x1D, 0x21, 0x66, 0x09, 0x09, 0x4F, 0x9C, 0x88, 0xFD, 0x89, 0x9B, 0x04, 0xBF, 0x5E, 0x32 }

PBL_APP_INFO(MY_UUID,
             "Pomade", "Jon Speicher",
             0, 1, /* App version */
             RESOURCE_ID_MENU_ICON_POMADE,
             APP_INFO_STANDARD_APP);

AppContextRef application_context;
AppTimerHandle timer;

#define POMODORO_COOKIE 1
#define POMODORO_TICK_PERIOD_SEC 1
#define POMODORO_TICK_PERIOD_MS  POMODORO_TICK_PERIOD_SEC * 1000

static Pomodoro pomodoro;

void select_clicked(ClickRecognizerRef recognizer, void* context) {
  if (pomodoro.running) {
    app_timer_cancel_event(application_context, timer);
    pomodoro_abort(&pomodoro);
    vibes_double_pulse();
    timer_window_show_restart();
  } else {
    timer = app_timer_send_event(application_context, POMODORO_TICK_PERIOD_MS, POMODORO_COOKIE);
    pomodoro_init(&pomodoro);
    timer_window_set_time_remaining(pomodoro.time_left_string);
    pomodoro_start(&pomodoro);
    timer_window_show_abort();
  }
}

void click_config_provider(ClickConfig **config, void* context) {
  config[BUTTON_ID_SELECT]->click.handler = select_clicked;
}

void handle_timer(AppContextRef ctx, AppTimerHandle handle, uint32_t cookie) {
  if (cookie == POMODORO_COOKIE) {
    pomodoro_decrement_by_seconds(&pomodoro, POMODORO_TICK_PERIOD_SEC);
    timer_window_set_time_remaining(pomodoro.time_left_string);

    if (pomodoro.complete) {
      vibes_long_pulse();
    } else {
      timer = app_timer_send_event(application_context, POMODORO_TICK_PERIOD_MS, POMODORO_COOKIE);
    }
  }
}

void handle_init(AppContextRef ctx) {
  application_context = ctx;
  resource_init_current_app(&APP_RESOURCES);

  pomodoro_init(&pomodoro);
  timer_window_init();
  timer_window_set_time_remaining(pomodoro.time_left_string);
  timer_window_set_click_config_provider(click_config_provider);
  timer_window_push();
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .timer_handler = &handle_timer
  };
  app_event_loop(params, &handlers);
}
