# To Do

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
    * Lots of pointer parameters to functions ought to be const
* There are some leaky abstractions
    * The segment view knows that the window it's added to has an action bar
    * The pomodoro controller initializes the segment view and the countdown
      view in a specific order to ensure that the resultant layer Z order is
      correct
    * A timer window "class" or something could help with this but that seems
      like overkill at this point
