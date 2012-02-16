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
---------
. R117 (1K) added to B-E junction of Q3
. All resitor/capacitor/inductor part values normalised to Japanese '5K1' format. 
  This is partly why the factroy missed R107/8/9/10. It also helps getting KiCAD's
  BOM file to match up with our BOM spreadsheet.

PCB
---
. All six (x4) push button switch holes enlarged to allow factory assembly, without manual adjustments to component legs.
. Changes made around Q2/Q3 pseudo RS-232 buffers to improve waveform profiles. R117 was added. Other resitros were reduced in value.
. All six (x4) push button switch holes enlarged (2.2 x 1.1mm) to allow factory assembly, without manual
  adjustments to component legs without (flattening with pliers etc.)
. A 1K resistor R117 was added to the RS-232 TX buffer Q3. Pull-down R76 lowered to 3K9. Resistor values around Q2 
  were lowered from 10K to 5K1. Done to improve waveform profiles.

