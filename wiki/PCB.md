<img src='http://gruvin9x.googlecode.com/svn/wiki/PCB.attach/pcbv4_photo.jpg' align='right' width='320'>
<h1>Custom Main Board Development</h1>

<i>Photo to the right is the v4.0 prototype (R.I.P). An image of the V4.1 board can be found below, in the 'Progress' section.</i>

<h2>Update 2012-09-23</h2>
The second batch of <a href='http://gruvin9x.com/shop/gruvin9x/22-gruvin9x-v41-pcb-fully-assembled.html'>G9X v4.2 fully assembled and tested boards</a> have been on sale at gruvin9x.com for a few weeks now. Sales are progressing steadily, indicating continually expanding interest.<br>
<br>
Meanwhile, we are having the Chinese factory also do small runs of the RTC/SD-card and gProg boards, which should result in further resale price reductions. <i>Yay!</i> \o/ More to come on this, as information comes to hand.<br>
<br>
<h2>Past Update 2012-05-14</h2>
The first test run of v4.1 fully assembled boards is sold out. We are in the quoting phase with the factory over the latest v4.2 design. (Very little difference from v4.1.) We hope to have some stock of the v4.2 boards by the end of July. Timing is very difficult to predict, due to several factors.<br>
<br>
Blank v4.1 boards are still available for purchase at <a href='http://gruvin9x.com/shop'>http://gruvin9x.com/shop</a>. There's also still the "pre-soldered tricky parts" version, with the MCU and LCD ZIF socket pre-soldered, while stocks last.<br>
<br>
<b>gruvin9x firmware is now <a href='http://en.wikipedia.org/wiki/Deprecation'>deprecated</a></b>, having been replaced by the far more advanced <a href='http://open9x.googlecode.com'>open9x</a>.<br>
<br>
<i>Gruvin</i>

<hr />

<h2>Why a custom PCB?</h2>

The primary intention with this new main board is to provide a more powerful and flexible platform for the TH/ER/gruvin9x/(RadioClone?) open source firmware to run on – basically, because we want to and we can. :p (See project home page if you don't know what that even is :-)<br>
<br>
The design is "open", so you can follow its progress in all details, as well as make requests and suggestions for additions or improvements – and, of course, you can get involved more directly and do those for yourself. (There are currently two contributors working on the PCB board design.)<br>
<br>
Initial intentions were to ...<br>
<br>
<ul><li>provide a programming header capable of supporting an onboard USB programming board. (For now, this header simply enables connection of an AVR ISP programmer.) <b>done</b>
</li><li>add RS-232 and TTL level telemetry serial data send/receive ports <b>done</b>
</li><li>free up most of PORTB for use with an MM/SD card interface for mass storage <b>done</b>
</li><li>upgrade the processor for more program, RAM and EEPROM storage memory <b>done</b> (v3.2)<br>
</li><li>upgrade processor yet again to 100-pin version, for even greater "plug'n'play" flexibility. <b>done</b> (v4.0)</li></ul>

Thanks to the enthusiastic support of several people over the months, there have been many ideas to come along since those first intentions were realized. These include ...<br>
<br>
<ul><li>USB port for potential 'game controller' interface -- for use with PC flight simulators, giving access to all switches and rotary inputs controls. <i><code>[</code> Sadly, a USB boot loader cannot happen due to space needed for SD card version of the same.<code>]</code></i>
</li><li>SD card boot loader. This would allow re-Flashing by simply copying the firmware file to the SD card. No more programmers or cables to connect and get working.<br>
</li><li>Two continuous rotation control dials with push switch action (rotary encoders) for improved menu navigation, value settings and in flight adjustment (yet to be coded.)<br>
</li><li>At least eleven (11) spare I/O ports including three ADC inputs for uses mostly not even planned yet.<br>
</li><li>Onboard support for both the Smartieparts.com EL backlight board and also now a dedicated LED backlight regulator.<br>
</li><li>Support for both the stock buzzer and a variable tone speaker at the same time, as well as a separate vibrator motor port with it's own regulated supply.<br>
</li><li>JTAG programming/debug port in addition to the separate SPI programming port. (Should prove invaluable for the code developers.)<br>
</li><li>RS232 and TTL level telemetry data interface, supporting shared simultaneous three-way connection with a host computer for debugging and analysis<br>
</li><li>Onboard precision voltage reference to improve safety main battery voltage monitoring over the Atmega's slow-to-stabalise internal band gap reference.<br>
</li><li>A theoretically much more robust and multi-vendor compatible trainer port circuit, hopefully meaning that your upgraded '9X will work seamlessly with just about any other make of radio currently on the market.</li></ul>

... and more besides.<br>
<br>
<b>Why not an ARM chip?</b>

We looked at basing the new board around a STM32 ARM based chip. But we decided against this, for a number of reasons. The ATmega2560 chip will do everything we need with the confidence that our highly timing-sensitive code is already tested and reliable on the ATmega platform.<br>
<br>
When we want more CPU power, say for on-board wireless video feed processing and other advanced features we have in mind, then we're more likely to add a second processor, so as to maintain the required high reliability of the core function -- that is, solid and safe remote control of our models.<br>
<br>
<h2>License</h2>

The custom board design is licensed under the <a href='http://www.tapr.org/TAPR_Open_Hardware_License_v1.0.txt'>TAPR Open Hardware License v1.0</a>. The license is very similar to the GPL of this project's related firmware source code, but includes additional protection against what your author terms, 'hostile patent acts'. In other words, like the GPL license for software source code, the TAPR Open Hardware License seeks to ensure that the openness of the design will endure. The license is NOT a non-commercial license. This design <i>is</i> able to be used by licensees for commercial purposes, under the terms of the <a href='http://www.tapr.org/TAPR_Open_Hardware_License_v1.0.txt'>OHL License</a>.<br>
<br>
<h2>Where it Started</h2>

As a starting point -- and in fact initially only as a test case to help learn to use the CAD software -- a PCB design was worked up from scratch in <a href='http://kicad.sourceforge.net/'>KiCAD</a> (itself also open source) to closely replicate the wiring and functions of Turnigy V2 '9X logic board. See <a href='http://code.google.com/p/gruvin9x/source/browse/#svn/trunk/pcb/original'>/trunk/pcb/original/</a> (as of <a href='https://code.google.com/p/gruvin9x/source/detail?r=155'>r155</a>). From there, things just kept growing, with numerous changes and additions being made, until eventually an actual new board ended up being produced.<br>
<br>
The first custom prototype PCB actually built was (somewhat oddly) named, "version 2.14". This was Gruvin's first ever PCB using tiny surface mount components and a lot was learned through the exercise. That said, the board fired up and worked from the moment power was first connected, which was quite astonishing at the time, to say the least! A few minor bugs were found, additions and changes made and another design quickly got underway.<br>
<br>
Version 3.2 used the same ATmega2561 chip, which was an upgrade over the original but with still only 64 pins. At the time, Gruvin was basically too scared to attempt a design for the 100 pin ATmega2560 version of the chip. As fate would have it however, a British gent by the name of Cameron happened across the project and asked if he might have a crack at the 100 pin design. "Well sure you can!" The rest is now history and as of 2011-09-13, we're about to start beta testing custom PCB version 4, which will finally (most hopefully) be offered up for retail, as a fully assembled unit. (As of said date, the first v4 test board is already up and running with no bugs yet found.)<br>
<br>
- - - -<br>
<br>
<blockquote>I was asked to make a video of the actual v3.2 board that I had hand constructed.<br>
Here it is ...</blockquote>

<blockquote><a href='http://www.youtube.com/watch?feature=player_embedded&v=V-QUrYAcJOU' target='_blank'><img src='http://img.youtube.com/vi/V-QUrYAcJOU/0.jpg' width='425' height=344 /></a> -- gruvin (on a bad hair day.)</blockquote>

<blockquote>Note: Video is X-Y mirrored, for some strange reason.</blockquote>

<blockquote>- - - -</blockquote>

<blockquote>And here I am again, flipped 'round the right way this time, showing the v4.1 board ...</blockquote>

<blockquote><a href='http://www.youtube.com/watch?feature=player_embedded&v=msiBt5J-OHc' target='_blank'><img src='http://img.youtube.com/vi/msiBt5J-OHc/0.jpg' width='425' height=344 /></a></blockquote>


<h2>Progress</h2>
<h3>The V4.1 Board -- Now Available</h3>

The v4.1 (final v4 production version) board is now available for purchase at <a href='http://gruvin9x.com/shop'>http://gruvin9x.com/shop</a>. We encourage all early adopters and home electronics constructors to grab yourselves a board or two and get building. :-D We'll be here to assist with any problems.<br>
<br>
<img src='http://gruvin9x.googlecode.com/svn/wiki/PCB.attach/pcbv41_photo.jpg' />

A high resolution version of the above photo is available <a href='http://gruvin9x.googlecode.com/svn/wiki/PCB.attach/pcbv41_photo_fs.jpg'>here</a>.<br>
<br>
Interestingly, this board was mainly constructed through concurrent, ambidextrous use of two hand soldering irons (one in each hand), to transfer components from the v4.0 prototype to the new v4.1 PCB. The process took about four hours in total. One resistor was apparently heat-damaged and needed replacing. Everything else seems to be working 100%. Yay \o/<br>
<br>
The back of the board has the HobbyKing LED back-light kit supplied self-adhesive foam pad stuck to it. I would recommend that specific LED back-light kit to all V4.1 board adopters. There's a dedicated driver output for it at the upper right of the board. <i>Be SURE to use the center GND and <b>RIGHT</b>-hand pin to get the current limited LED-safe connection</i> -- because the left terminal is a full current, 5V supply!<br>
<br>
<img src='http://gruvin9x.googlecode.com/svn/wiki/PCB.attach/pcbv41_photo_back.jpg' />

<h3>The v4.0 Prototype Board</h3>

Here's a recent V4.0 3D visualization from KiCAD...<br>
<br>
<img src='http://gruvin9x.googlecode.com/svn/wiki/PCB.attach/pcb_v4.x_3d_top.gif' />

<h2>Current Status</h2>

2011-12-08: First v4.1 board fully built and tested all OK. Boards in stock and available for purchase at <a href='http://gruvin9x.com/shop'>http://gruvin9x.com/shop</a>

2011-11-16: v4.1 blank production boards have arrived. Also, v4.1 factory assembled 'beta' boards are underway and expected before Christmas.<br>
<br>
2011-10-11: We are satisfied that the v4.1 board is ready for its first test factory production run of ten Beta test boards. All of the testing is finished and the bugs found have been corrected. Meanwhile, we continue to develop and test on the three existing and working v4.0 boards, which have all been patched using track-cuts and wire links to the new v4.1 bug-fixed design version. It is likely that Cam will finalise the decision to freeze and deliver the v4.1 design to Leo for factory processing within the next 24 hours.<br>
<br>
2011-09-22: A number of circuitry bugs have been found and corrected, as testing continues on schedule. Four v4.0 boards are known to exist at this time. We expect to be ordering the first small factory test batch by mid October, but will not rush the date if all testing has not been completed satisfactorily.<br>
<br>
2011-09-13: The first v4.0 beta test board was assembled and powered up by Gruvin in New Zealand, who was excited to see it perform all its primary functions without fault, right from the get go! :-D The additional v4 features are yet to be tested. There are two or three others at different locations around the globe also building the same v4 board as this is being typed. Assuming all goes well, thanks to a generous donation offered by Swiss supporter, Leo, ten v4.1 boards are planed to be factory assembled in China, with about half of those being offered at near cost to the first group of beta testers outside of the core project team. If all that goes well, then we plan to try and raise funds for assembly batches of 50 to 100 boards at a time, with a target retail price of around USD$149. No promises can be made at this stage.<br>
<br>
<b>Past Milestones in descending date order ...</b>

2011-08-21: The fist ten (blank) V4 prototype boards have arrived in cam's hands. At least two other project followers have asked for blank boards to build up from scratch themselves. Great stuff -- more beta testers! :D<br>
<br>
In the meantime, we have received several expressions of interest from people wanting to purchase a new controller board for themselves. <b>But we are not currently accepting pre-orders</b>. We need to wait until, a) the V4 board is tested to be without errors, b) the Chinese manufacturer lined up to assemble the small quantities of boards involved has proven practical and c) a fair and proper mechanism for placing orders is available. We're working on it. Please be patient. We do hope to have assembled and tested boards available before the end of 2011.<br>
<br>
2011-07-07: First test run V3 PC boards confirmed in production.<br>
<br>
2011-07-04: New SD card board (smaller/better size) sent away for production. Also, Cam has made an alternative design for UK builders who, like him, cannot find local stock for the SD card socket used in the previous design.<br>
<br>
2011-06-25: SD card PCB assembled, installed and test OK. Physical size of board found to be 8mm too long for its decided installation position and the SD card socket should protrude beyond the board edge by 2.5mm also. Changes made to the design accordingly, awaiting ordering process. (Real Time Clock (RTC) on the same board also tested and working.)<br>
<br>
2011-06-01: SD card prototype PCBs arrive. Construction begins, noting that the custom component pads are all perfectly correct. Yay \o/.<br>
<br>
2011-01-14: First prototype board fully constructed, code updated and functioning. There were some issues with the wiring layout of the trim switches that will need to be fixed on the V3 board. But otherwise, everything seems to be working.  All in all, it doesn't make much sense to produce another V2 prototype board, since the V3 board will include several fixes and enhancements.<br>
<br>
Next step is probably going to be to take advantage of the extra Flash space (now 256KBytes) and start playing with MM/SDCARD mass storage.<br>
<br>
2010-12-30: Components and PCBs have arrived (ahead of schedule). Have ordered components to make up the 'plug' end of the 2-way, 3-way and 8-way JST sockets, which I had thought were included with same. I'm elated to report that the PCB mounting holes and push-button-switch physical locations are within spec and fit well into the actual radio '9X cabinet. (That had been one of my greater concerns during the design process.)<br>
<br>
2010-12-22: <a href='http://gruvin9x.googlecode.com/svn/trunk/pcb/rev2.14-frozen/production/gruvin9x-bom.xls'>Components</a> to build three prototypes ordered from Digikey.com<br>
<br>
2010-12-15: A first batch of 10 (MOQ) prototype PCB's (<a href='http://gruvin9x.googlecode.com/svn/trunk/pcb/rev2.14-frozen'>rev2.14</a>) ordered.<br>
<br>
<h2>Schematics and PCB Design Files</h2>

See the <a href='Circuitry.md'>Custom Schematics</a> page for details.<br>
<br>
<br>
<h1>Historical Data</h1>
<h2>Preview</h2>

2010-12-02: A final draft of the PCB based on <a href='http://gruvin9x.googlecode.com/svn/trunk/pcb/rev2.1/gruvin9x_rev21.pdf'>schematic rev2.1</a> has been completed. (All files updated in <code>/trunk/pcb</code> as at <a href='https://code.google.com/p/gruvin9x/source/detail?r=159'>r159</a>). I'm waiting on some peer review and comments before committing this to a manufacturer. Time frame unknown.<br>
<br>
The board includes the total re-wire of all trim and button switches into a 4x4 scanned matrix to free up most of Port B. This gives us dedicated I/O ports for the MMC/SDCARD and a couple spares as well -- with theoretically only very minor CPU load for scanning the inputs.<br>
<br>
The connector for the MMC/SDCARD interface can be seen at lower/middle of the image below. The two connectors to the lower right are the TTL and RS-232 level telemetry TX/RX ports. A 2-pin connector on the upper edge is for the left-hand and right-hand trim switch 'common' connections. These replace their respective connections to ground, in order to work with the new 4x4 input matrix.<br>
<br>
This new main board will receive an <b>ATmega2561</b> (256K Flash, 4K EEPROM, 8K SRAM). I have thus far decided to keep ATmega running at 5V, though it's certainly tempting to move down to 3.3V, since the LCD screen and SDCARD currently need a total of 31 resistors just to down-convert the voltage! However, I'm concerned about possible noise increase on the ADC inputs, should the operating voltage be lowered, and a couple of other minor issues too. So at 5 Volts we stay.<br>
<br>
<b>The 3D image from KiCAD</b> as at <a href='https://code.google.com/p/gruvin9x/source/detail?r=155'>r155</a> ...<br>
<br>
<img src='http://gruvin9x.googlecode.com/svn/wiki/PCB.attach/kicad-pcb-r21-3d-top.jpg' />

NOTE: Since moved on to rev2.11 with a few minor changes/additions, like RF decoupling caps on the KEYXn inputs and some tidying up here and there. Work continues! :-D<br>
<br>
<br>
<h3>Previously</h3>

NOTE: These images (below) as at <a href='https://code.google.com/p/gruvin9x/source/detail?r=122'>r122</a> ...<br>
<br>
<img src='http://gruvin9x.googlecode.com/svn/wiki/PCB.attach/PCB-final-mock.jpg' />

The above image is merely a PhotoShop mock-up based on the various layer outputs from KiCAD.<br>
<br>
<h3>Cost</h3>

The present best quote for low volume PCB manufacture is around the USD$15 mark -- for one of 10 boards with no components installed. Manufacturing of a prototype board will likely not happen until at least the telemetry and mass storage mods have been done. That will include break-outs for any remaining spare port pins and should get the hardware to a point where nothing additional is needed.<br>
<br>
<img src='http://gruvin9x.googlecode.com/svn/wiki/PCB.attach/kicad-pcb-3d-top.jpg' />

<img src='http://gruvin9x.googlecode.com/svn/wiki/PCB.attach/kicad-pcb-3d-bottom.jpg' />