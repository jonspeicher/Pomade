// ----------------------------------------------------------------------------
// Pomade - A pomodoro-tracking Pebble watchapp with statistics on your wrist
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include <pebble_app.h>

#include "cookies.h"
#include "countdown_controller.h"
#include "version.h"

// Define the app's unique identifier and metadata.

#define APP_UUID {0x78, 0x1D, 0x21, 0x66, 0x09, 0x09, 0x4F, 0x9C, \
                  0x88, 0xFD, 0x89, 0x9B, 0x04, 0xBF, 0x5E, 0x32}

PBL_APP_INFO(APP_UUID, APP_NAME, APP_AUTHOR,
             APP_VERSION_MAJOR, APP_VERSION_MINOR,
             RESOURCE_ID_APP_MENU_ICON, APP_INFO_STANDARD_APP);

// Event handlers -------------------------------------------------------------

void handle_init(AppContextRef ctx) {
  resource_init_current_app(&APP_RESOURCES);
  countdown_controller_init(ctx);
}

void handle_timer(AppContextRef ctx, AppTimerHandle handle, uint32_t cookie) {
  // TBD: Is it worth retrieving this from the controller somehow? Would it
  // ever need to be chained? - JRS 8/15
  if (cookie == COUNTDOWN_COOKIE) {
    countdown_controller_timer_event(handle);
  }
}

// main -----------------------------------------------------------------------

void pbl_main(void* params) {
  PebbleAppHandlers handlers = {
    .init_handler = handle_init,
    .timer_handler = handle_timer
  };
  app_event_loop(params, &handlers);
}
