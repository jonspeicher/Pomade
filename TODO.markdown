# To Do

* Pomodoro -> Interval and `pomodoro_` and `break_` functions
* Logic to keep `long_break` and `short_break` and `pomodoro` and manage
  transitions; maybe a separate sequence tracker that the timer asks for the
  next interval or something?
    * pomodoro complete -> long or short break
    * pomodoro abort -> pomodoro
    * break complete -> pomodoro
    * break abort -> pomodoro
* Pull string out of interval, add a `format_time` function like for pebble
  that snprintfs into a caller's string
* Add a stats module that tracks complete and aborts
* Add a stats page that shows percentages and averages and MTBI
* Need a way to show interval type on main page
    * Show completed/aborted stats on main page?
    * Or show how many pomodoros left to long break?
    * Consider "four bubbles" and the word "break?"
* Consider separating countdown controller and bubble controller somehow?
    * Separate the views?
    * Even though they're the same "window"?
    * countdown controller/counter controller, and...what kind of window?
    * Perhaps the countdown controller can be "given" the bubble controller and
      the stats or something?
    * Or the window stays as a "timer window" (or something) and is created by
      the app in "main", and the window is passed to both the countdown
      controller and the "bubble" controller, and each adds its own controls?

## One architectural idea

* Have a sequencer or something
    * Tell it (POMODORO, ABORT) or (SHORT BREAK, COMPLETE) or (POMODORO,
      COMPLETE, #4) and it fills up the next interval for you
* Have a counter thingum that draws the bubbles on the countdown window
    * It would have to be created with a pointer to the window so that it could
      add its own layers
* Maybe there's a pomodoro controller
    * It would work with the countdown controller
    * It would regiters callbacks with it for interval abort/complete events
    * It would work with the stats controller and work with the bubble
      controller

## How far can/should DI be taken?

* `create_countdown_window` to create a struct with a `Window*` and
  pointers to functions to set text, etcetera?
* Would that struct be defined by the countdown controller?
* Who would populate the struct (the dependency injector?)
* Who would pass it in to the controller (the dependency injector?)
* With a Pebble `Window*` most of the OS APIs could be used, and those probably
  wouldn't be DI'd, but I suppose they could be if you wanted to do crazy
  testing, but surely the sample code and models don't go to that extent
