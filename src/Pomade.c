#include <pebble_os.h>
#include <pebble_app.h>
#include <pebble_fonts.h>

#include "pomodoro.h"

#define MY_UUID { 0x78, 0x1D, 0x21, 0x66, 0x09, 0x09, 0x4F, 0x9C, 0x88, 0xFD, 0x89, 0x9B, 0x04, 0xBF, 0x5E, 0x32 }

PBL_APP_INFO(MY_UUID,
             "Pomade", "Jon Speicher",
             0, 1, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer timer_layer;

AppTimerHandle timer;
#define POMODORO_COOKIE 1
#define POMODORO_TICK_PERIOD_MS 1000
#define POMODORO_TICK_PERIOD_SEC POMODORO_TICK_PERIOD_MS / 1000

static Pomodoro pomodoro;

void handle_timer(AppContextRef ctx, AppTimerHandle handle, uint32_t cookie) {
  if (cookie == POMODORO_COOKIE) {
    pomodoro_decrement_by_seconds(&pomodoro, POMODORO_TICK_PERIOD_SEC);
    text_layer_set_text(&timer_layer, pomodoro.time_left_string);

    if (pomodoro.complete) {
      vibes_long_pulse();
    } else {
      app_timer_send_event(ctx, POMODORO_TICK_PERIOD_MS, POMODORO_COOKIE);
    }
  }
}

void handle_init(AppContextRef ctx) {
  pomodoro_init(&pomodoro);

  window_init(&window, "Pomade");
  window_stack_push(&window, true /* Animated */);

  text_layer_init(&timer_layer, window.layer.frame);
  text_layer_set_text_alignment(&timer_layer, GTextAlignmentCenter);
  text_layer_set_font(&timer_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  text_layer_set_text(&timer_layer, pomodoro.time_left_string);
  layer_add_child(&window.layer, &timer_layer.layer);

  timer = app_timer_send_event(ctx, POMODORO_TICK_PERIOD_MS, POMODORO_COOKIE);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .timer_handler = &handle_timer
  };
  app_event_loop(params, &handlers);
}
