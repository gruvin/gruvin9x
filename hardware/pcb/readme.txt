This PCB is a rework of Gruvin's V3.0 PCB to use the 100pin ATMega 2560. It was primarily done to enable the 
use of JTAG debugging and also to free up some pins for future fun. (Cam). Most of the work was done by Cam,
which has been just wonderful. Thanks Cam! (Gruvin)

============================
= Differences V4.1 to V4.2 =
============================

. All six (x4) push button switch holes enlarged to allow factory assembly, without manual adjustments to component legs.
. Changes made around Q2/Q3 pseudo RS-232 buffers to improve waveform profiles. R117 was added. Other resitros were reduced in value.

============================
= Differences V4.0 to V4.1 =
============================

. Switched PB0 and PB6 (PPM_OUT and IDL2_SW) assignment around to allow for a hardware PPM_OUT solution.
. After the above change we discovered we couldn't use PB0 (/SS) as an input for IDL2_SW.
  Unfortuantely when hardware SPI is used PB0 (/SS) can only be used for output, so we switched PB0 and PB4 (IDL2_SW and SD_CS)
  We now have:
  PIN         V4.0          V4.1            
  PB0 (/SS)   PPM_OUT   SD_CS
  PB4         SD_CS     IDL2_SW
  PB6 (OC1B)  IDL2_SW   PPM_OUT
. Switched the PPM_IN pull down resistor (R80) to pull up, worked better that way.
. Added components for a soft off switch.
. A few net name changes, Spare4 and Spare3 became Spare1\LED-BL-opt and Spare2\Vib-opt, and some net name changes for the soft off addition.
. In the move round for the soft off switch I mananged to add another decoupling cap around the CPU (C64)
. LED backlight fix. Needed NPN transistor to switch the P-FET.
. Changed the series LED backlight resistor to 200 ohms from 100 ohms, it looked better.
. Polarized caps are now indicated on the silkscreen.
. Jumper J4 graphic on schematic changed to show the config we are currently using as default.
. SDCard board connector moved to be more central, fits easier this way, at least for me.
. SDCard board also renamed to avoid confusion between the two versions.
. Up switch moved down 0.2mm.
. Addition of a fuse to the K5 LED back light header. We really need to implement a fuse to protect the whole board but without a
  total rip up it isn't going to happen. The fuse took the space of R103 which was removed, it was felt it was not needed.
. Broke the 3.3v rail out and a fused BATT+
. BOM also updated to reflect changes.


============================
= Differences V3.0 to V4.0 =
============================

Major
-----
* Replaced 64 pin AMega 2561 with 100 pin 2560
* Removed the 4066. Gruvin felt it bad for not offering enough protection to the CPU incase of user misconnects. So 
  it had to go. We now have seperate output buffer transistors to the module and the trainer jack. 
* Added a filter cap around Q1 to try and stop spurious switching when the buzzer sounds.
* Added voltage dividers to the four spare ADC pins, these may be used for monitoring individual Tx cell voltages,
  or anything, thought it useful to provide voltage dividers onboard.  
* Removed matrix for push buttons to make the board a true drop in replacement.  
* Added JTAG header
* Changed 10pin ISP header to 6pin
* Added breakout headers for spare pins, the whole of port L, half of port F (4x ADCs), and port H (inc. a second 
  serial port)
* Remaining 4 pins broken out to test point pads here and there.
* Switched the I2C interface to use hardware I2C pins 
* Switched the ADC usage from port F to port K to free up JTAG pins
* Added interfacing, connectors etc. for two rotary encoders as per Multiplex Evo sets (Hardware debouncing 
  with a little RC network). Added these on pins with interrupt triggers just in case needed.
* Switched pin for IDL_SW1 with Spare1 just to make routing easier
* Signals KEY_Y2 and KEY_Y3 have replaced the digital GND signals on the 9 pin headers that go to the pot gimbals 
  and trim switches. Because the trim buttons are now in a switch matrix, digi GND is no longer needed but the 
  matrix signals KEY_Y2 and KEY_Y3 are. On the V3 board these signals came out on a separate 2 pin header but this 
  can be avoided by doing this.
  ** NOTE ** The switch matrix requires a little mod/fix to operate correctly. On both of the horizontal 
  trim PCBs the trim switches are connected to analogue GND and not digi GND as they should be. In order for the 
  matrix to operate correctly we must remove the connection to analogue GND (by cutting PCB traces) and connect it 
  across to the digi GND point (now the KEY_Yn point) on the vertical trim board. 
  Pictures for this mod are in the .\Data Sheets\Switch Matrix Changes\ directory
* Added circuity to drive a vibrating motor for alarms etc. Have used a variable voltage regulator with enable signal
 (1.2v - 5.5v @ 500ma). This should hopefully allow a selection of motors to be used. Have also added a jumper 
 that either allows the Spare_2/PG5 signal or the PH3/OC4A PWM ouput to drive the enable on the regulator. I think 
 PWM control maybe an overkill but the option is there. Early indications show PS3 controller vibration motors 
 look good, they wedge in just fine in the bottom left of the back of the case (to the left of the battery 
 compartment). Got a copy ps3 wired controller from eBay for 6GBP. Contains two motors with differing weights, 
 either seems fine.
 Have tried driving the TPS77601 enable input with a PWM signal of around 250Hz while using one of the PS3 motors 
 and it seems fine. Have uped filter capacitors from the datasheet to try and keep noise generated low. The current
 combination of caps represent the lowest noise I have managed to get on both the motor side and the input side.
 
Minor
-----
* Added mounting holes into schematic so they don't disappear if you tell the netlist update to delete components 
  it can't find 
* Amalgamated the projects KiCAD libraries, and restructured their directories to better reflect KiCAD's own 
  library structure. (They confuse me less this way)
  
  
=======================================
= For reference V2.14 to V3.0 changes =
=======================================

* Change of speaker to PWM pin (provides MUCH cleaner tonnes, too.)
* Existing speaker output retained on original pin also -- this was in fact intended for vibrating motor (optionally.)
* Added breakout of I2C (This was more of a change to the SDcard interface)
* Added transistor in PPM_IN linen (Principal reason was for buffering/amplification.)
* Added breakout of Back Light signal, Vcc, and GND to 3 pin header
* Rearranged stick/trim switch interface wiring to remove awkward/stuffed-up cross-over bug. (This is a biggie!)
* Fix of reversed Collector and Emitter connections on Q3
* Small corrections to hole and switch positions. V2.14 was well within acceptable tolerances though.


=====================
= Component changes =
=====================
I renamed a few library parts that also exist in the standard KiCAD libraries to avoid confusion. 

These items are usually standard KiCAD parts that have been copied to the Gruvin library and tweaked a 
little for the needs of the project or to fix errors. These and only these parts have been given the 
_GRUVIN suffix on top of the normal KiCAD name. Original Gruvin library parts are just named normally.

I also edited a few parts.

The diffs are:

Footprints/Modules
------------------
SM0603        -> SM0603_GRUVIN         Silkscreen outline different
PIN_ARRAY_3X1 _> PIN_ARRAY_3X1_GRUVIN  Larger spacing and different 3D representation
PIN_ARRAY_3X2 -> PIN_ARRAY_3x2_GRUVIN  Bigger pads & didn't like 3D representation in std KiCAD part
PIN_ARRAY_4X2 -> PIN_ARRAY_4X2_GRUVIN  Bigger pads & no 3d rep
PIN_ARRAY_4X1 -> PIN_ARRAY_4X1_GRUVIN  Bigger pads & no 3d rep
PIN_ARRAY_5X2 -> PIN_ARRAY_5X2_GRUVIN  Bigger pads on 8 pins
SW_PUSH_6x4MM                          Bigger pads

Schematic components
--------------------
ATMEGA2560-A  -> ATMEGA2560-A_GRUVIN   Would you believe the standard KiCAD part has two power pins missing !
ATMEGA64      -> ATMEGA64_GRUVIN       Not sure, need to ask Bryan
CONN_30       -> CONN_30_LCD_GRUVIN    Added the tabs of the SMT LCD connector in, also put LCD in the name.
