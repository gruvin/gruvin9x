This folder contains the current "under development" version of the various PCBs.

MAIN PCB
========
This PCB is a rework of Gruvin's V3.0 PCB to use the 100pin ATMega 2560. It was primarily done to enable the 
use of JTAG debugging and also to free up some pins for future fun. (Cam). Most of the work was done by Cam,
which has been just wonderful. Thanks Cam! (Gruvin)

=============================
= Differences V4.1a to V4.2 =
=============================

SCHEMATIC
=========

-- Gruvin --
. R117 (1K) added to B-E junction of Q3. Nearby resistor values halved. This
  all to improve higher speed (125,000 Baud) signal shapes.
. All resistor/capacitor/inductor part values normalised to Japanese '5K1'
  format. This is partly why the factory missed R107/8/9/10. It also helps
  getting KiCAD's BOM file to match up with our BOM spreadsheet.
. C65 added for cautionary extra MCU power decoupling
. PORTHH rearranged and upgraded to include GND and VCC pads.
. USB connector K6 flipped to make pin 1 GND.
. R118 (10K bleed resistor) added across C63 in the soft-off circuit.
. Added pad P11 to enable easier connection to C-of-Q9 for 'short-to-ground'
  power on option (for replacement trainer jacks.)

-- Cam --



PCB
===

-- Gruvin --
. All six (x4) push button switch holes enlarged to allow factory assembly,
  without manual adjustments to component legs.
. Changes made around Q2/Q3 pseudo RS-232 buffers to improve waveform
  profiles. R117 was added. Other resistors were reduced in value.
. All six (x4) push button switch holes enlarged (2.2 x 1.1mm) to allow
  factory assembly, without manual adjustments to component legs (without
  flattening with pliers, etc.)
. A 1K resistor R117 was added to the RS-232 TX buffer Q3. Pull-down R76
  lowered to 3K9. Resistor values around Q2 were lowered from 10K to 5K1.
  Done to improve waveform profiles.
. PORTH 'hack pads' P20 upgraded to 10-pin IDC header with VCC and GND.
  (Required significant reworking of nearby modules/routing.)
. 'Fat track thermal sink' issues address over the entire board (reduced 
  track thickness to small part pads where practical.)
. Several cases of 'ground looping' resolved. (Use single, common tie 
  points instead of 'loops' whenever possible.)
. A number of right-angle track bends resolved to 45-degrees. (Sharp 
  corners can cause problems with copper etching.)
. Added R118 (across C63 -- soft-off circuitry.)
. Added P11 (trainer jack 'short to ground' power-on option.)

-- Cam --

