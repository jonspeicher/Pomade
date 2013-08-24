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
* Will drift be a problem?
    * Initial timing tests seem to indicate that it won't (~1-2 sec over 25 min)
    * Drift mitigation could happen in the timer handler in the countdown
      controller where the timer is restarted at the end of the handler if
      the countdown hasn't elapsed
