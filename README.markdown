Pomade
======

This is [Pomade](https://github.com/jonspeicher/Pomade), a
[pomodoro](http://www.pomodorotechnique.com)-tracking
[Pebble](http://getpebble.com) watchapp with statistics on your wrist.

Description
-----------

Pomade is designed to allow you to practice the pomodoro technique wherever you
take your Pebble, handling the timing and sequencing of the technique
automatically. In addition, Pomade will track pomodoro statistics so that you
may measure your success and diagnose issues.

Minimum Requirements
--------------------

Pomade was built and tested with Pebble firmware v1.12.1 and version 1.2.1 of
the Pebble iOS app. It should work with version 1.9.4 of the Pebble Android
app, but I have not specifically tested it. Pomade was built with version 1.12
of the Pebble SDK.

Installation and Uninstallation
-------------------------------

Pomade can be installed and uninstalled by following the standard procedure for
your mobile phone type. See http://help.getpebble.com for more information.

Usage
-----

Pomade is designed to stay out of your way while enforcing good pomodoro
technique.

* To begin a pomodoro or a break, press the "select" button when the start icon
  (▶) is displayed in the action bar.
  
* To cancel a pomodoro or a break, press the "select" button when the cancel 
  icon (X) is displayed in the action bar. Pomade will produce two quick
  vibrations.
  
* To restart a cancelled pomodoro, press the "select" button when the restart
  icon (↺) is displayed in the action bar.

When a pomodoro or break completes, Pomade will produce a single, long
vibration and show `0:00` to indicate that the segment is complete.

Pomade won't allow you to proceed to a break if you abort your in-progress
pomodoro unless you then restart and successfully complete that pomodoro, but
it will allow you to abort a break and proceed directly to the next pomodoro if
you so desire.

Release History
---------------

See https://github.com/jonspeicher/Pomade/releases.

Source and Contributions
------------------------

The source for Pomade is available at https://github.com/jonspeicher/Pomade.

To clone and hack:

    git clone https://github.com/jonspeicher/Pomade.git
    <pebble-sdk>/Pebble/tools/create_pebble_project.py --symlink-only <pebble-sdk>/Pebble/sdk Pomade
    cd Pomade && ./waf configure && ./waf build

See `TODO.markdown` in the repository's top-level directory for a list of
planned additions and technical improvements that I may or may not ever get
around to.

Author
------

Jon Speicher (jon.speicher@gmail.com)

License
-------

Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)  
Licensed under the MIT license: http://opensource.org/licenses/MIT
