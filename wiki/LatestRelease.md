# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.


# Latest Stable Pre-Compiled Binaries #

## codename Frisky ##

The latest, stable public maintenance release of gruvin9x firmware is code-named 'Frisky' and lives at [/branches/frsky](http://code.google.com/p/gruvin9x/source/browse/#svn%2Fbranches%2Ffrsky).

There are four versions of binary (.hex) files you can download for flashing your '9X, without needing to compile from source.

These versions carry the latest bug-fixes and stable new features. Each file relates to one of the four most common hardware modification configurations -- including the stock standard, unmodified radio.

### Version Info for Binary Files Below ... ###
![http://gruvin9x.googlecode.com/svn/branches/frsky/svnversion.gif](http://gruvin9x.googlecode.com/svn/branches/frsky/svnversion.gif)<br />

## Binary .hex Download Links ##
You may have to, "right-click / Save target/link as ..." to get these links to save as local files.

### Custom  Controller Board v4.1 ###
  * **[gruvin9x.hex](http://gruvin9x.googlecode.com/svn/branches/frsky/gruvin9x.hex)** -- V4.1 Custom PCB -- current stable release.

.
### Unmodified '9X Radio Version ###

  * **[gruvin9x-stock.hex](http://gruvin9x.googlecode.com/svn/branches/frsky/gruvin9x-stock.hex)** -- For stock hardware with no internal re-wiring.

.
### Modified (Stock) '9X Radio Versions ###

  * **[gruvin9x-std-speaker.hex](http://gruvin9x.googlecode.com/svn/branches/frsky/gruvin9x-std-speaker.hex)** -- For [speaker upgrade](SpeakerReplacement.md) only. No other wiring modification. (This version also works with the stock beeper, for softer sounding tones.)

  * **[gruvin9x-frsky-nospeaker.hex](http://gruvin9x.googlecode.com/svn/branches/frsky/gruvin9x-frsky-nospeaker.hex)** -- [Fr-Sky telemetry](FrskyInterfacing.md) mod, but no speaker upgrade.

  * **[gruvin9x-frsky-speaker.hex](http://gruvin9x.googlecode.com/svn/branches/frsky/gruvin9x-frsky-speaker.hex)** -- [Fr-Sky telemetry](FrskyInterfacing.md) and [speaker upgrade](SpeakerReplacement.md) mods in place.

.
### Other Versions ###

For this with v3.2 or other legacy hardware versions, you will need to [compile from source code](CompilingFromSource.md).