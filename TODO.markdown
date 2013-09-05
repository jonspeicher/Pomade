# To Do

* BETTER ICONS!
* Add fancy flyout animation when changing the segment view from pomodoro to
  break and vice-versa
* Make pomodoro, short, and long break intervals configurable?
* Add a stats module that tracks complete and aborts
* Add a stats page that shows complete/abort percentages, averages, and etc.
* Will drift be a problem?
    * Initial timing tests seem to indicate that it won't (~1-2 sec over 25
      min)
    * Drift mitigation could happen in the timer handler in the countdown
      controller where the timer is restarted at the end of the handler if the
      countdown hasn't elapsed
* The code isn't bulletproof
    * Null pointers aren't checked
