# This project superseded by [opentx](https://github.com/opentx/opentx) and [Fr-Sky's Taranis](http://www.frsky-rc.com/product/pro.php?pro_id=113) #

The gruvin9x project was launched in October of 2010 and retired some time in 2012. A massive amount of work has since been done over at the [opentx](https://github.com/opentx/opentx) project, which was forked from gruvin9x by Bertrand Songis, in France. Bertrand is an incredibly talented programmer and has achieved far more than I (Gruvin) ever could have. I fully support [opentx](https://github.com/opentx/opentx) and _highly_ recommend it.

Fr-Sky's [X9D Taranis](http://www.frsky-rc.com/product/pro.php?pro_id=113) is a high quality unit, shipped with open source [opentx](https://github.com/opentx/opentx) firmware as standard. The [Taranis](http://www.frsky-rc.com/product/pro.php?pro_id=113) represents just about everything the gruvin9x project could have ever wished for and at a very fair price. Indeed, the G9X project was originally inspired by our desire to utilise Fr-Sky's two way telemetry radio modules. So we are thrilled that Fr-Sky were the ones to create the world's first commercial open source RC controller and we support their ongoing endeavours enthusiastically.

(Note: Gruvin has absolutely no affiliation with Fr-Sky. I doubt they even know who I am. :P)

The **openrc community** now resides at [Open RC Forums](http://openrcforums.com/forum/). They're a great bunch. Go check them out.

**This site remains online as a historical record, only.** Original content follows ...

<img src='http://gruvin9x.googlecode.com/svn/wiki/About.attach/turnigy9x_v4.gif' align='right'>
<h1>Summary Introduction</h1>

This project started out as a kind of 'place holder' for the author's personal circuitry upgrades, hacks and mods to his <a href='http://code.google.com/p/er9x/'>ER9X</a>-powered Turnigy 9X V2 RC transmitter. Over time, some more supporting documentation and random notes were added. Then Gruvin went kind of crazy one weekend and wondered if he could create a whole new, replacement controller board, to make wiring extra things to his transmitter easier. KiCAD PCB design software was chosen, because it is open source. A few prototype boards came to fruition. Then Cam (UK) came along and asked if it would be OK to have a go at installing the 100-pin ATmega2560 MCU, instead of the 64-pin ATmega2561, which Gruvin used. "Sure! Go for you life!" Cam did a great job and all that eventually resulted in what the, "G9X v4.2 Custom Controller Board".<br>
<br>
Several additional utility board designs were started and added to the project, including an RTC/SD-card interface, a custom USBasp Flash programmer and a multiplexer system, which enables the splitting of a single receiver channel into several additional control outputs. There's also been work on an audio playback module (for spoken telemetry warning etc) which appears to have mostly moved to the open9x project, as at this writing.<br>
<br>
<h1>Project Detail</h1>

The initial main focus was around adding and enhancing Fr-Sky telemetry support and the development of an <a href='PCB.md'>upgraded main logic board</a> -- for <a href='Telemetry.md'>telemetry</a> support in general, as well as a better ATmega chip and MMC/SDCARD support for model data and general mass storage in FAT16/32 format.<br>
<br>
Compatibility with the stock V2 '9X transmitter will be retained as far as possible. So fear not. There will "always" be a gruvin9x version available to run on the stock unit. There will also be different binary versions available to support the most common manual circuit hacks for telemetry (and other things) that do <i>not</i> require the <a href='PCB.md'>new PCB</a>.<br>
<br>
The first true stable, public release of gruvin9x was made in January, 2012. The release is code named, 'Frisky', is community verified 'stable' and thus believed to be essentially 'bug free'. (I hope I haven't jinxed anything by typing that! :-P)<br>
<br>
Work continues for the next version, being mostly focussed on the new V4 custom controller board, though with improvements and added features also slated for the stock radio controller board.