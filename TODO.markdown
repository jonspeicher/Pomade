# To Do

* Pomodoro -> Interval and `pomodoro_` and `break_` functions
* Logic to keep `long_break` and `short_break` and `pomodoro` and manage
  transitions
    * pomodoro complete -> long or short break
    * pomodoro abort -> pomodoro
    * break complete -> pomodoro
    * break abort -> pomodoro
* Pull string out of interval, add a `format_time` function like for pebble
  that snprintfs into a caller's string
* Factor out window and action bar stuff into a separate "class" or module
* Add a stats module that tracks complete and aborts
* Add a stats page that shows percentages and averages and MTBI
* Need a clean way to delegate clicks to different windows/controllers/etc if
  there is a stats page
* Need a way to show interval type on main page
    * Show completed/aborted stats on main page?
    * Or show how many pomodoros left to long break?
    * Consider "four bubbles" and the word "break?"
* `version.h` with defines for name, "company", major/minor
