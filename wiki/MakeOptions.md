# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.


# Make Options (gruvin9x) #

**ER9X.C/H FILENAME CHANGE NOTICE** -- As of gruvin9x [revision 179](https://code.google.com/p/gruvin9x/source/detail?r=179), all occurrences or 'er9x' have been changed to 'gruvin9x'. I had planned to leave er9x in place, as I figured it did no harm. But things started getting too confusing when switching between versions. I ended up accidentally editing the wrong file in the wrong directory. So it is done.

## Makefile Defaults ##

By default, simply running 'make' from the `src/` directory will build gruvin9x.hex in the configuration preferred/needed by Gruvin -- this project's owner. As of [revision 186](https://code.google.com/p/gruvin9x/source/detail?r=186), running `make` with no arguments is equivalent to ...

```
make EXT=FRSKY BEEPER=SPEAKER USART1=FREED
```

The Makefile also defaults to the 'usbtiny' AVR programmer type, since that's what Gruvin uses. Oh and, it disables flash verification by default also -- to save time.

## Hardware Modification Related Make Options ##

<ul>
<li>EXT=<br>
<br>
Values: STD, FRSKY (default), JETI<br>
<br>
This is for when you've freed ports E0 (ThrCut) and E1 (AilDR) for telemetry data use by moving those two switch inputs to unused pins PC6 and PC7 respectively.<br>
<br>
</li>
<li>BEEPER=<br>
<br>
Values: BUZZER, SPEAKER (default)<br>
<br>
This is for when the stock "on/off" electronic beeper/buzzer has been replaced with a small speaker. This enables varying frequency tones for keypad beeps, alarms, etc.<br>
<br>
</li>
<li>PPMIN=<br>
<br>
Values: STD, MOD1 (default)<br>
<br>
The MOD1 option is needed if the PPM-in compatibility hardware mod has been made on the '9X in question. See <a href='PpmIn.md'>PPM-in Compatability (hack)</a>

</li>
<li>USART1=<br>
<br>
Values: STD, FREED (default)<br>
<br>
This is for if you have freed USART1's TX/RX pins by moving LH_Trim_Up/Dwn switches to spare ports PC0 and PG2, respectively. Gruvin (but no one else to my knowledge) originally performed this hardware mod to free USART1 for use with USB Flash or SDCARD serial-driven interfaces. However, native SDCARD access via the SPI interface on Port B is planned with a new PCB design -- or at least an ATmega2561 upgrade chip on the stock PCB.<br>
<br>
USART1 may still be used at a later date. However, this mod is not compatible with PCB design rev2.11, which currently uses all of Port E (including the USART1 pins) for a 4x4 scanned key-switch interface.<br>
<br>
</li>
</ul>


## Standard TH/ER9X Make Directives ##

All other standard ER9X make commands remain present. Examples include ...

<blockquote><pre>*make wflash* [[PROGRAMMER=usbtiny]] - programs/flashes the ATmega64A using code data from gruvin9x.hex. (With optional programmer type override in [[brackets]] if your is not a 'usbtiny')<br>
<br>
*make reeprom TARGET=models* - reads the ATmega64A EEPROM (models/settings) data into models.bin<br>
<br>
*make weeprom TARGET=models* - writes models.bin to the ATmega64A EEPROM, restoring models/settings<br>
<br>
etc</pre></blockquote>