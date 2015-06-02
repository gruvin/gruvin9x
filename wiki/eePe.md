# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.


# Erazz's Amazing (Windows/Linux/Mac) eePe EEPROM File Manager #

Wow. All I can say is, "Wow". (I mean -- it must have taken some real time and effort and time to put this together. So much potential with this software for the future too.)

This Qt program (meaning it runs on Linux, Windows _and_ my beloved Mac) allows you to not only interrogate, but also re-program (ALL model settings), read/write from/to an EEPROM image (.bin) file. You can duplicate, move, shuffle model configurations with simple mouse movements -- create a whole new model map and setting from scratch, then save it toa new .bin/.hex file for uploading tot he 9X -- and even simulate model data using virtual mouse driven yokes, switches, knobs, etc. WOW. Did I say, "WOW?" Very cool :D

**eePe** does not support gruvin9x Fr-Sky extensions (yet) -- so beware that saving an EEPROM file in eePe will lose any Fr-Sky data. (No biggie at this stage.) As of gruvin9x `trunk/` [r377](https://code.google.com/p/gruvin9x/source/detail?r=377), the "file type 3" data format for Fr-Sky settings version 1 has been finalised.

Go to the eePe project home and donate the man all of this Friday night's beer money NOW -- That's an order! :-P Then -- only then :p -- download the program, install it and see what you think! (P.S: I'm exempt 'cause I don't buy beer on Fridays :p -- But I'll scratch something up from somewhere, some time. Promise!)

## Mac Users ##

Mac users can install the Qt Developer stuff from here: http://get.qt.nokia.com/qt/source/qt-mac-cocoa-opensource-4.6.2.dmg

Then svn checkout eePe from the eePe project site.

```
svn checkout http://eepe.googlecode.com/svn/trunk/ eepe
```

Under Windows and Linux, you build the eePe application like so ..

```
cd eePe/src
qmake
make
```

But on the the Mac, when you run `qmake`, which would 'normally' create a `Makefile` for the build process, a Makefile is _not_ created. Instead, and arguably even better, `qmake` creates an entire Xcode project structure in a directory named `eepe.xcodeproj/`. To build the program, open the project in Xcode, click _Build and Run_ and you'll be all set!

I'm going so enjoy hacking this one -- to add the Fr-Sky 'file-type 3' support that is. No forks this time of course! It's been years since I last wrote anything that used Qt and ...

> _By the way -- have you taken a fresh look at Qt v4 in the last couple years? It's come a LONG way and is now fully OS X Cocoa integrated. I didn't know! (Head-in-the-sand syndrome strikes again.)_

> After you install the Qt4 Developer package (as above), be sure to read the README and run the demo ...

```
open /Developer/Applications/Qt/qtdemo.app
```

> And to think I was considering using xWidgets to get cross-platform coding done. Pfft!