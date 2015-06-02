# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.

# Porting gruvin9x Fr-Sky features to ER9X #

It was asked in an RC Groups [forum post](http://www.rcgroups.com/forums/showthread.php?t=1266162&page=237&highlight=gruvin9x#post16819009) if the gruvin9x features will be included in ER9X -- and conversely, if gruvin9x will keep up with feature and bug changes in ER9X. Hre's a copy of the answer I gave, including brief instructions for porting the gruvin9x Fr-Sky stuff over to ER9X, should anyone wish to do that at some point.

> _This copy is here for instructional archive reasons. If you want to follow the conversation, you should start at the [forum post](http://www.rcgroups.com/forums/showthread.php?t=1266162&page=237&highlight=gruvin9x#post16819009)_


---

#### BEGIN QUOTED TEXT ####

I've been trying to keep a half an eye on the developments or ER9X since [r262](https://code.google.com/p/gruvin9x/source/detail?r=262) -- but as you say, "nearly every day". So I'm afraid it's inevitable that the two projects will diverge -- if only for lack of time to manually merge in the changes on either side.

Also, alas, it's inevitable that some core files get changed eventually, making keeping things in sync more difficult. In this case, it's happened already. For example, I've had to move a bunch of stuff out of `menus.cpp` and into a new file menus.h, so that the menu functions can be included for use in `frsky.cpp`. The alternative was to keep adding more and more code to `menus.cpp`, whereas keeping as much of the Fr-Sky stuff in one place made more sense to me.

Of course, anyone who is set up to contribute code to ER9X (including Erazz of course) can do this themselves. I'm happy to help by answering questions where needed. Conversely, if there's any bug fixes/features introduced into ER9X that people think gruvin9x needs -- then present a case. I'm all ears.

### Porting - A Brief How-To ###

In case someone does decide to take this on, then ...

Briefly, if you search all the `.cpp` and `.h` files for "FRSKY" (case sensitive), then you'll find all the places I've wedged in conditional code, between `#ifdef FRSKY` and `#endif directives`. (NOTE: There's changes in `menus.cpp` to the existing ER9X FRSKY code, which came before gruvin9x.)

Off the top of my head, that list includes `menus.cpp`, `menus.h` (see below), `myeeprom.h`, `file.h`, `file.cpp`, `er9x.h` and `er9x.cpp`. Oh and `pers.cpp`. (NOTE: Files, `er9x.*` are named `gruvin9x.*` in the gruvin9x project.)

The other thing then, is the splitting of `menus.cpp` into `menus.cpp` and `menus.h`. Essentially, you just have to copy my `menus.h` file, delete all the duplicate lines in `menus.cpp` and stick an `#include "menus.h"` at the top of `menus.cpp`.

Then you just need to add `frsky.h` and `frsky.cpp` from the gruvin9x tree. (2010-12-16: Currently in `branches/frsky/` -- _not_ in `trunk/`.)

Easy peasy! (not?)

If anyone is going to take this on, then may I suggest you WAIT until I get to the point of merging the Fr-Sky features into the gruvin9x trunk -- otherwise you could be wasting a lot of effort and have to re-trace your tracks, several times. It's highly unlikely ER9X will change in a way that will break the Fr-Sky stuff. So waiting should do no harm.

Hope that helps somehow, more that is frustrates!

Finally -- I'm sure that any particular feature not in either version that you may want will be kindly considered by either developer(s).