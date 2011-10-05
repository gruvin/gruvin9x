This folder contains the current "under development" version of the V4.x 
PCB.

Only files that differ from the latest frozen V4.x PCB will be found in this directory.

Library file are duplicated regardless as they are needed for viewing the PCB etc.

Changes between the latest frozen V4.x PCB and this development version are:

. Switched PB0 and PB6 assignment around to allow for a hardware PPM_OUT solution.
. Fixed bug with /SS being used a input for the IDL2 switch, unfortuantely when hardware SPI is used /SS can only be used for output.
. Added components for a soft off switch.
. LED backlight fix.
. Polarized caps are now indicated on the silkscreen.
. SDCard board connector moved to be more central, fits easier this way, at least for me.
. SDCard board also renamed to avoid confusion between the two versions.
. Up switch moved down 0.2mm.
. Addition of a fuse to the K5 LED back light header. We really need to implement a fuse to protect the whole board but without a
  total rip up it isn't going to happen.
. BOM also updated to reflect changes.
