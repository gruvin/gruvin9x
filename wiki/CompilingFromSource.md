# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.


# Compiling gruvin9x from Source #
**NOTE:** Intended for Mac OS X audiences. Details for Windows (and mention of Linux) can be found in the original TH/ER9X project document [Flashing the 9x.pdf](http://gruvin9x.googlecode.com/svn/trunk/doc/Flashing%20the%209x.pdf).

## Downloading the gruvin9x Source Code ##

The gruvin9x project is fully version-tracked using Subversion, or `svn`. There are various way s of getting Subversion installed on your Mac, but in the author's opinion, the best way for a OS X based code developer is to simply install Apple's Xcode AKA Apple Developer Tools, with the Unix Dev option ticked. Xcode comes free with each version of OS X on the installation DVD. Subversion will be installed as part of all that.

To download the complete gruvin9x project source, enter the following command at a shell prompt ...

```
~$ svn checkout http://gruvin9x.googlecode.com/svn/trunk/ gruvin9x
```

This will create a folder named `gruvin9x` in the folder you were in when you ran the command. Of course, the gruvin9x folder can then be safely renamed or moved anywhere you like.

To build the firmware code ready for programming (having first installed [CrossPack](http://www.obdev.at/products/crosspack/) for that purpose), change to the `gruvin9x/src/` directory and execute `make`. Briefly ...

Our default Makefile is supplied as Makefile.dist. So you should initially copy that to Makefile ...

```
cp Makefile.dist Makefile
```

To build the correct version of gruvin9x to work on an not-modified, factory standard '9X, use ...

```
make clean; make PCB=STD
```

or, if you want variable tone frequency beeps etc., this will also work without installing a speaker ...

```
make clean; make PCB=STD BEEPER-SPEAKER
```


To build for the v4.1 custom controller board (with all default feature options) ...

```
make clean; make PCB=V4
```

Running make with no parameters is not really encouraged. Doing so will build the project in such a way as matches the latest development controller board and Gruvin's default options.

To build gruvin9x for a modified stock controller board, with the [telemetry](TelemetryMod.md) and [speaker](SpeakerReplacement.md) mods enabled ...

```
make clean; make PCB=STD EXT=FRSKY BEEPER=SPEAKER
```

Please see the comments throughout `Makefile.dist` itself or the [Make Options](MakeOptions.md) wiki page for more detail.

## Flashing the 9X Using Make ##

You can manually flash the ATmega64A using AVRDUDE as described on the [Connecting a Flash programmer to your '9X](FlashGuide.md) wiki page. Or you can use the more conveninet `make` method, which includes all the necessary options for you. (You may want to edit Makefile for your particular programmer set-up.) ...

```
make wflash
```

HINT: Add something like `AVRDUDE_PROGRAMMER=usbtiny` to specify a different programmer, or edit Makefile to change the default.

### Backing up the EEPROM ###
The gruvin9x firmware store user settings and model programming data in the ATmega64A on-board EEPROM. **This gets erased** each time you re-flash the firmware! To take a backup ...

```
make reeprom TARGET=models
```

Again, you can include something like `AVRDUDE_PROGRAMMER=usbtiny` to specify a different programmer, or edit the Makefile to your preference. (The default target is gruvin9x.bin. The `.bin` extension is forcibly appended, so don't include it on the command line.)

**NOTE:** Until I get around to fixing it, the above command currently requires that the .bin file already exists. You can create an empty file by executing the command ...

```
touch models.bin
```

### Miscellaneous ###

If you want to take a peek inside the EEPROM backup data file, try something like [0xED](http://www.suavetech.com/0xed/0xed.html).

**CODE SIZE:** The complete ER9X compiled code base as at [revision 262](https://code.google.com/p/gruvin9x/source/detail?r=262) appears to be less than 48KBytes — including the 8K splash screen graphic. The ATmega64 has 64KBytes of FLASH program memory and 4KBytes of static RAM. If I’m reading the data properly, only about 400 bytes of the RAM is currently in use. (Seems low though?) In any case, things are looking good for adding all of the presently planned functionality.

## Reporting Issues ##

Please report any wiki documentation errors or code bugs using the Google Code [issues](http://code.google.com/p/gruvin9x/issues) menu link.