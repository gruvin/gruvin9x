# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.

# Fr-Sky Interfacing #

Gruvin (more or less) followed the original TH/ER9X 'JETI' wiring instructions to get RS-232 (TTL level) TX and RX signal for my Fr-Sky two-way transmitter module. Those instructions can be found [here](http://code.google.com/p/er9x/wiki/JETI).

Below, you'll find similar and extra detail of exactly how I hooked up my Fr-Sky unit.

## Accessing TXD and RXD on the ATmega ##

The ATmega RXD and TXD special-purpose pins are used for simple switch inputs in the factory '9X -- namely, Throttle-Cut and Aileron-D/R, respectively.

To free these pins up for use with serial data, we need to move those two switches elsewhere. The two pins chosen for their new home were pins 41 and 42, or PC6 and PC7 respectively.

The modification requires the use of _really fine_ wire. I used 0.2mm, enamelled copper wire. You can also use fine, insulated wire, salvaged from the newer (yet now old) high-density computer IDE cables. Each of these wires is a _single-core_, PVC insulated wire. You most definitely do _not_ want to try and use any kind of multi-strand wire -- no matter how fine it it is.

**IMPORTANT**: The main reason to use _really_ fine wire may not be what you think. It is certainly possible (though more difficult) to use heavier, stronger wire. But doing so will increase the risk of accidentally damaging the delicate ATmega chip's pins. (Think of it as using a wrecking bar to pick your teeth -- or something like that! :P) In practice, the slightest accidental tug by 'big fat, shaky, human hands on a big fat wire', can quite literally rip an ATmega pin right of the chip. Trust me -- _use really fine wire!_

### Re-wiring Procedure ###

Referring to the image below ...

  * Remove the two left-hand-most resistors as indicated in yellow
  * Hot glue a couple of 220ohm resistors (1/8th or 1/4watt are OK) to a nearby, clearish area of the PCB
  * Solder your 'super fine' wires to pins 41 and 42 of the ATmega and connect to the top end of the resistors as shown. Use alcohol if required -- to steady your hands! (Just joking -- but if it works for you -- go right ahead. :p)
> _HINT: Pre-solder the wire end and the ATmega pins. Use a solder sucker or de-soldering wick to clear away excess solder from the two pins and to remove any solder bridge. Then lay the first wire end over the pin and apply the soldering iron directly down on top of it for half a second, then directly straight up -- then let go the wire. Give the wire a gentle tug in the direction directly away from the chip (in line with the pin).If it holds -- you're done. Don't futz with it. If you're right handed, solder the left hand wire first, so the the soldering iron does not lay over the first wire when trying to solder the second._
  * Solder wires from the bottom ends of the hot-glued resistors to the little vias (holes) near where the two removed resistors were, as shown in the image.

> ![http://gruvin9x.googlecode.com/svn/wiki/FrskyInterfacing.attach/frsky-wiring.jpg](http://gruvin9x.googlecode.com/svn/wiki/FrskyInterfacing.attach/frsky-wiring.jpg)


**NOTE:** It pays to use small dabs of hot-glue near the ATmega pins and in a couple of places along the wires to hold them in place. The last thing you want is for something to get hooked under them and rip them off, possibly damaging the ATmega pins in the process!

## The Interface ##

Fr-Sky, in their wisdom, decided to use RS-232 voltage levels for their interface, rather than provide a more modern 5V TTL-to-serial USB interface. We tried to talk them out of it, but they stuck to their guns. Oh well.

What this means is that you need to invert and voltage-shift the signals to and from the Fr-Sky transmitter module, so they can play happily with the 5 Volt ATmega chip. There are specialised 5V TTL to RS-232 chips to do this, "properly". But we show here is a simple and in fact _advantageous_, discrete transistor method.

> _Advantageous? Well yes, actually. The method shown below allows the transmitter module to still operate -- for both hosts simultaneously -- when connected to an external serial interface, say on a computer -- while not having to disconnect the internal wiring to the '9X. With the values shown, most computers will take precedence over the internal 9X ATmega micro in terms of sending (transmitting) data to the Fr-Sky module. **More useful even**, is that you don't have to disconnect the telemetry interface for re-Flashing. Clever huh! (In truth, this was a lucky fluke! :P)_

> _That said, be careful not to have your Fr-Sky two-way receiver switched on during re-flashing, as the stream of data_will_collide with the ISP programming signals and could mess up your ATmega chip._

Here is the discrete transistor circuit ...

> ![http://gruvin9x.googlecode.com/svn/wiki/FrskyInterfacing.attach/frsky-interface.png](http://gruvin9x.googlecode.com/svn/wiki/FrskyInterfacing.attach/frsky-interface.png)<br />
**NOTE** An earlier version of the above circuit had the collector and emitter of Q3 reversed. The circuit as shown here now is correct. (This circuit is clipped from the full schematic of the gruvin9x [custom controller board](PCB.md).)

Any general purpose NPN and PNP transistors should work for the components marked Q2 and Q3, respectively. The BC847/857 devices are in fact SMD surface mount versions, as used in the new PCB design we're working on.

For the prototype, Gruvin actually used a dremel too to carve up the mostly unused, legacy PCB mounted inside the '9X rear casing to build the above circuit 'dead bug' style. (A photo is not presently available.)

**ADDENDUM**: A future version of this circuit (v4.2) uses 5.1K-Ohm resistors in place of all the 10K and a 1K across Q3's E/C leads to improve the 'squareness' of the TX signal for use with DSM2 modules at 125,000bps. This change is in no way required for 9600 Baud Fr-Sky operation however.

## Ground Loops (WARNING) ##

Gruvin found that the Fr-Sky module refused to operate correctly if a ground (GND) wire was connected between the Fr-Sky module's rear RX/TX/GND pins and the level-shifting circuit above. The problem was probably RF energy pick-up through the ground-loop created by having two ground wires -- one where the module plugs into the 9X and the other from the serial data port. **Solution:** simply do not connect the ground wire as shown as pin-1 on the connector-K2 in the circuit above. Others have since said that they had no such problem. YMMV

### ER9X Compatible ###

In case you're wondering, this wiring modification is 100% compatible with the JETI and Fr-Sky telemetry extensions in the [ER9X](http://er9x.googlecode.com/) firmware, too.