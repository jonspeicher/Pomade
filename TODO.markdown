# To Do

* Need a way to show interval type on main page
    * Show completed/aborted stats on main page?
    * Or show how many pomodoros left to long break?
    * Consider "four bubbles" and the word "break?"
* Add a stats module that tracks complete and aborts
* Add a stats page that shows percentages and averages and MTBI
* Will drift be a problem?
    * Initial timing tests seem to indicate that it won't (~1-2 sec over 25 min)
    * Drift mitigation could happen in the timer handler in the countdown
      controller where the timer is restarted at the end of the handler if
      the countdown hasn't elapsed
* The code isn't bulletproof
    * Null pointers aren't checked
