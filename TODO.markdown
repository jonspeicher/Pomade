# To Do

* Logic to keep `long_break` and `short_break` and `pomodoro` and manage
  transitions; maybe a separate sequence tracker that the timer asks for the
  next interval or something?
    * pomodoro complete -> long or short break
    * pomodoro abort -> pomodoro
    * break complete -> pomodoro
    * break abort -> pomodoro
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
    * Or the window aggregates two "interfaces"; one for countdown, one for
      bubbles, and the interfaces are passed in to each controller but the
      window is created as a whole and is the "pomodoro timer window"
          * Either the interfaces also point to functions to operate on them or
            there are specific APIs for dealing with the interface objects and
            potentially building them as well (or they're built by the window
            so that they can be located appropriately
          * That's probably the answer: in the window c'tor, say "create a
            bubble object at x,y" and "create a countdown object at "a,b" via
            bubble object and countdown object APIs, then give those structs
            out to the controllers

## One architectural idea

* Have a sequencer or something
    * Tell it (POMODORO, ABORT) or (SHORT BREAK, COMPLETE) or (POMODORO,
      COMPLETE, #4) and it fills up the next interval for you
* Have a counter thingum that draws the bubbles on the countdown window
    * It would have to be created with a pointer to the window so that it could
      add its own layers
* Maybe there's a pomodoro controller
    * It would work with the countdown controller
    * It would register callbacks with it for interval abort/complete events
    * It would work with the stats controller and work with the bubble
      controller
    * Maybe it would be a state machine or something for sequencing

## How far can/should DI be taken?

* `create_countdown_window` could create a struct with a `Window*` and
  pointers to functions to set text, etcetera?
* This would then be given to the controller to remove the hard-coded calls to
  the view API?
* Who would define the struct? The controller? The window?
* Who would populate the struct? The dependency injector, e.g. main?
* Who would pass it in to the controller? The dependency injector, e.g. main?
* With a Pebble `Window*` most of the OS APIs could be used, and those probably
  wouldn't be DI'd, but I suppose they could be if you wanted to do crazy
  testing, but surely the sample code and models don't go to that extent
* To get totally crazy, the "Interval" abstraction could have a struct with
  pointers-to-functions too, as those calls are hard-coded into the controller
  at this point as well
* What am I trying to accomplish? Polymorphism? Testing?
