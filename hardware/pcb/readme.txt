This folder contains the current "under development" version of the V4.x 
PCB.

Only files that differ from the latest frozen V4.x PCB will be found in this directory.

Library file are duplicated regardless as they are needed for viewing the PCB etc.

Changes between the latest frozen V4.x PCB and this development version are:

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
. BOM also updated to reflect changes.
