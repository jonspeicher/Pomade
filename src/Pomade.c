#include <pebble_os.h>
#include <pebble_app.h>
#include <pebble_fonts.h>

#include "timer_controller.h"

#define MY_UUID { 0x78, 0x1D, 0x21, 0x66, 0x09, 0x09, 0x4F, 0x9C, 0x88, 0xFD, 0x89, 0x9B, 0x04, 0xBF, 0x5E, 0x32 }

PBL_APP_INFO(MY_UUID,
             "Pomade", "Jon Speicher",
             0, 1, /* App version */
             RESOURCE_ID_MENU_ICON_POMADE,
             APP_INFO_STANDARD_APP);

void handle_timer(AppContextRef ctx, AppTimerHandle handle, uint32_t cookie) {
  if (cookie == TIMER_CONTROLLER_COOKIE) {
    timer_controller_periodic_event(handle);
  }
}

void handle_init(AppContextRef ctx) {
  resource_init_current_app(&APP_RESOURCES);
  timer_controller_init(ctx);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .timer_handler = &handle_timer
  };
  app_event_loop(params, &handlers);
}
