# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.

# Getting Wired #

**UPDATE** 2011-11-24: Current versions of AVRDUDE do not seem to work well with the Sparkfun USB Pocket Programmer. I have switched to a USBasp based USB programmer and it is now working flawlessly. Original article (to be updated) continues ...


<img src='http://gruvin9x.googlecode.com/svn/wiki/FlashGuide.attach/usbpktprog.jpg' align='left'>The first thing you will need is one of the many available AVR programmer kits. Perhaps you already have an AVR programmer? I purchased a <a href='http://www.sparkfun.com/commerce/product_info.php?products_id=9825'>USB Pocket Programmer</a> from Spark Fun. It works really well and is not at all expensive. (<a href='http://sparkfun.com'>SparkFun</a> have a some really cool stuff by the way. Stop by for a while and check them out!)<br>
<br>
You'll need to connect your programmer's ICP (In-Circuit Programming) cable to your '9X. There are a few options available.<br>
<br>
An excellent "solder-less" example, using <a href='http://www.sparkfun.com/commerce/product_info.php?products_id=8870'>pogo pins</a>, can be found in the offering from <a href='http://SmartieParts.com'>SmartieParts.com</a> (Steven / s_mack on <a href='http://www.rcgroups.com/forums/'>RCGroups forum</a>). With this option, all you need is a screw-driver! The board includes a USB programming interface and an EL back-light driver for your LCD screen. I believe it even comes with an EL back-light sheet. See <a href='http://www.rcgroups.com/forums/showthread.php?t=1338412#post16549680'>here</a> for detailed information with images, in the form of a mini-review, by Erazz (of ER9X).<br>
<br>
Here, I will discuss the, "soldering wires straight to PCB" method.<br>
<br>
There is an excellent PDF guide for Windows users <a href='http://gruvin9x.googlecode.com/svn/trunk/doc/Flashing%20the%209x.pdf'>http://gruvin9x.googlecode.com/svn/trunk/doc/Flashing%20the%209x.pdf</a>, which also shows how to connect an AVR programmer ribbon cable to the '9X. That guide though seems to rely on a colour coded cable to determine what wire goes where. So I've included a photo below of my 'classic all-grey' ribbon cable installation, with numbered wires, for your convenience.<br>
<br>
When I ordered my SparkFun Pocket Programmer, I had them add a spare programming cable. I cut the two 'remote' connectors off the end of that and used what remained to wire up my radio. Here's a photo of my installation, using a stock SparkFun cable as described ...<br>
<br>
<blockquote><b>IMPORTANT:</b> The picture below shows a typical ‘V2′ transmitter, as has been shipping for a few months as at time of this writing. The V1 unit  had an error on the PCB where the ‘SCK’ programming pad (wire 7 below) was connected one pin too far left on the ATmega64 chip. So watch out for that! If you have a V1 unit, you can still get things going. You just have to careful to get a wire soldered to the right place.</blockquote>

<blockquote><img src='http://gruvin9x.googlecode.com/svn/wiki/FlashGuide.attach/progwiring.jpg' /></blockquote>

<ul><li><b>NOTE:</b> The two little hot-glued resistors to the left, with their respective fine wires comprise the re-wiring necessary to free up the ATmega serial comms port (RXD/TXD) for telemetry data. Those pins are otherwise connected to the Throttle-Hold and Aileron-DR switches. For telemetry support, the switches get moved to two spare pins (PC6/7). <b>This mod is only necessary if</b> you intend using a Fr-Sky enabled <a href='TrunkBinaries.md'>binary</a> image -- or specifying the EXT=JETI or EXT=FRSKY <code>make</code> attributes, when building from source. <b>See <a href='FrskyInterfacing.md'>here</a> details of what to connect where and how</b>.</li></ul>

<h2>Programmers with 6-pin ISP Connectors</h2>

If you have a more modern AVR programmer with a 6-pin ISP connector, you can find more appropriate wiring information on the <a href='GProg.md'>gProg wiki page</a>.<br>
<br>
<h1>Flashing the Firmware</h1>

<h2>Software</h2>
<img src='http://gruvin9x.googlecode.com/svn/wiki/FlashGuide.attach/avrdude.jpg' align='right'><img src='http://gruvin9x.googlecode.com/svn/wiki/FlashGuide.attach/crosspack.jpg' align='right'>Whilst I'm no stranger to Windows, I strongly prefer using my Mac for all development work. Fortunately, so do many others who work with Atmel AVR chips, so there’s a nice packaged installer named <a href='http://www.obdev.at/products/crosspack/'>CrossPack</a> that has everything you need for cross-compiling C/C++ AVR code on your Mac.<br>
<br>
CrossPack also comes bundled with <a href='http://savannah.nongnu.org/projects/avrdude/'>AVRDUDE</a>, which is used to operate the programmer hardware. Even more conveniently, the 'usbtiny' programmer protocol driver that the SparkFun USB Pocket Programmer I randomly chose is also included and installed, ready-to-run as part of the CrossPack bundle. Very cool! Best of all, you don't have to do any configuring of this software. Just install it and then move on to the steps below.<br>
<br>
And yes, the above software is all free! Aint it great? Be sure to say thanks or drop a donation!<br>
<br>
<h2>Ready-to-Run "binary" firmware</h2>

There are (at the time of this writing) four pre-compiled hex file versions of gruvin9x available and kept up to date. The versions apply to the various different hardware mods/re-wiring you may or may not have chosen to do. You can download the version that is right for you from the <a href='TrunkBinaries.md'>TrunkBinaries</a> page, using same to flash your '9X without having to compile from source.<br>
<br>
<blockquote>See <a href='TrunkBinaries.md'>here</a> to for the binaries download page.</blockquote>

<h2>Flashing Ready-to-Run Firmware</h2>
You can now burn your <code>gruvin9x[-version].hex</code> file using AVRDUDE as follows ...<br>
<br>
<pre><code>avrdude -c usbtiny -p atmega64 -B 1 -U flash:w:gruin9x[-version].hex<br>
</code></pre>

AVRDUDE should find the USB programmer, whatever port it's connected to. If not, try unplugging the programmer and plugging it back in. (You'll probably need to do this at least once after installing CrossPack. No reboots are required! This is NOT Windows :p )<br>
<br>
The flash procedure will completely erase your ATmega64A chip's Flash program memory, write in the new firmware and then read back the code to verify it all went OK. After using gruvin9x for a while, you can take a backup of your model programming data using the following AVRDUDE command ...<br>
<br>
<pre><code>avrdude -c usbtiny -p atmega64 -B 1 -U eeprom:r:models.bin:r<br>
</code></pre>

... and you can restore that model data after any given re-flash using ...<br>
<br>
<pre><code>avrdude -c usbtiny -p atmega64 -B 1 -U eeprom:w:models.bin<br>
</code></pre>

Oh by the way; unless you happen to have a battery connected to the '9X (requires the 12-way back cover connector be installed) then leave the tiny little switch on the programmer PCB set to “Power Target”. The programmer will then power up the 9X -- albeit in a fashion it isn’t used to (some switches disconnected etc) and it will complain bitterly with lots of beeping. Block your ears and ignore those, because the new gruvin9x firmware flashing process will very soon put silence all the racket!<br>
<br>
<h1>What to Expect</h1>

After re-flashing for the first time, you can expect to feel a little anxious! Do not fret! The feeling is completely normal. :D<br>
<br>
Disconnect and tuck your programming cable away, for now, in such a way that allows you to put the rear cover back on the transmitter. You can tidy things up more once you know its all working.<br>
<br>
<blockquote><i>REMEMBER to reconnect the rear-cabinet cable connector! The first time I flicked the power switch after flashing I got absolutely nothing. Not even a beep or a flicker. “Uhoh!” ... then I realised that things would probably go better with the power and other things actually connected! :-P</i></blockquote>

During boot-up, the new firmware checks a few things. You’ll get one or more “alerts” on screen, like “Throttle not set idle” and a message like "Alert! Alarms disabled" — meaning the beeper is turned off, as it will be by default. Also, all switches have to be in the “off” state — that is, all front switches ‘up’ and top switches ‘back’. Oh and don’t worry — all these power-up warnings can be disabled through settings in the new '9X menus if you don’t want them. (I don't!)<br>
<br>
Once you clear the alerts away (by pressing <a href='EXIT.md'>EXIT</a> for each or satisfying the switch positions), you should see the (also optional) 'gruvin9x' splash screen'. From this point, things just get better and better ...<br>
<br>
The first thing you’ll want to do is set the ‘mode’ to ‘Mode 1′, for your throttle on the right, right? — since no one in their right mind would <i>ever</i> use Mode 2 now, would they? :P OK, maybe just a few folk might -- maybe even you. Mode 2 is in fact the default, and I have no plans to change that, actually.<br>
<br>
Oh! To access that system settings menu, press and hold <a href='LEFT.md'>LEFT</a> (original '+') button.<br>
<br>
On that note, now would be a really good time to give the <a href='http://gruvin9x.googlecode.com/svn/trunk/doc/ER9x%20Users%20Guide.pdf'>ER9X Users Guide</a> a thorough once-over. If you haven't already realised, I think you'll be impressed with how powerful this firmware is. It truly does completely transform an otherwise rather average "Chinese '9X" radio into something a lot of fun to own and use.<br>
<br>
<h1>Compiling from Source</h1>

Please see the <a href='CompilingFromSource.md'>Compiling From Source</a> wiki page for details on this subject, including changes to the original Makefile defaults employed by gruvin9x.