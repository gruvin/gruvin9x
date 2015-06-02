<img src='http://gruvin9x.googlecode.com/svn/wiki/About.attach/s9xsplash-wiki.gif' align='right'>

<h2>G9X v4.x BOARD (DISCONTINUED)</h2>

Why? Because there's much better things on the horizon -- we think. Trusted sources confirm the ongoing development of a Fr-Sky X9D transmitter, which we understand will be supporting open9x firmware form launch. The board will be ARM 32-bit based and is rumoured to be targeting sub-USD$100 retail -- complete with Fr-Sky 16-channel transmitter module, built in. If this all turns out to be true, then the complete radio will cost less than the G9X board (in the small qty's we can manage) whilst having all the same features and more. So we wait.<br>
<br>
We simply don't know if demand for the G9X system will continue -- or not. Whilst orders seem to still be trickling in -- now even for blank boards (wow!) -- we don't expect that to last. Right or wrong, Gruvin made the choice, not to risk funds on another batch of G9X v4.2 boards. Was it the right choice? Have your say at <a href='http://9xforums.com/forum/viewforum.php?f=66'>9xforums.com</a>.<br>
<br>
<br>
<h2>We recommend open9x firmware</h2>

Please visit the open9x <a href='http://open9x.googlecode.com'>project site</a> for more information.<br>
<br>
Also highly recommended is the <a href='http://companion9x.googlecode.com'>companion9x</a> project -- the easiest way to obtain the latest release version of open9x firmware for your radio -- and much more. (Based on the original eePe from er9x.)<br>
<br>
<h2>Project Brief</h2>
<blockquote><i>First off, we especially wish to thank all the amazing original and ongoing work by</i>Thomas Husterer<i>of the <a href='http://code.google.com/p/th9x/'>th9x project</a>. A good number of other people have also contributed ideas, code and more to his, this and other related projects. THANK YOU all!</i></blockquote>

The gruvin9x project was originally forked from <code>er9x v1.1 r262</code> (<a href='http://code.google.com/p/er9x/source/browse/?r=262'>http://code.google.com/p/er9x/source/browse/?r=262</a>) which was based on a earlier version of the original th9x code. A huge amount effort was later put into the gruvin9x code base by contributor bsongis, of the <a href='http://open9x.googlecode.com'>open9x</a> and <a href='http://companion9x.googlecode.com'>companion9x</a> projects, which later became the sole point of focus for our custom hardware firmware support.<br>
<br>
<b>Highlights ...</b>
<ul><li><a href='About.md'>Project Wiki Documentation</a>
</li><li><a href='ReProgram.md'>Re-programming Your 9X Radio</a> -- firmware downloads, flashing, etc.<br>
</li><li><a href='PCB.md'>Custom Main Board Development</a> -- <b>upgrade your '9X controller board!</b></li></ul>

<h2>But what <i>is</i> it?</h2>
<img src='http://gruvin9x.googlecode.com/svn/wiki/About.attach/turnigy9x_v4.gif' align='right'>
In short, this is an RC modeller/hacker's dream come true. We get to use your own custom firmware in our radios, adding features and making changes whenever we like and all (generally) at much lower cost than comparable commercial gear -- especially in terms of firmware features and programmability. We currently support any PPM transmitter module, with a focus on Fr-Sky two-way products, as well as DSM, DSM2 and DSMX 'retro-fitted' modules, usually salvaged from cheap 4-ch bind'n'fly models, as found on eBay.<br>
<br>
Open9x firmware is written and maintained by active RC modellers. It is mature, stable and very powerful. Based on th9x's 'multiplexer' implementation, it is arguably a little difficult to learn compared to other systems -- but is much more flexible. Open9x firmware is a significantly more powerful replacement for the comparatively simple default factory firmware that comes with the '9X radios.<br>
<br>
The <a href='PCB.md'>gruvin9x custom controller board</a> was developed using a larger version of the original Atmel AVR chip, to give us more RAM, firmware code space and more I/O connections for additional peripherals, such as telemetry data port, RTC/SD-card interface and more.<br>
<br>
If your existing transmitter doesn't do something you wish it would, chances are that open9x already does. If it doesn't, then put in a feature request and, if it makes sense to others, then the firmware will likely soon perform your new function.<br>
<br>
Both the open9x firmware and the companion9x (desktop) projects support our poplar <a href='PCB.md'>G9X v4 Custom Controller board</a>.<br>
<br>
<blockquote><i><b>Caveat</b>: Firmware is  half the story -- quality of hardware is not a given and should also be carefully considered. Whilst the build quality of most 9X radios seems just fine, there have been notable exceptions. We therefore strongly recommend that all firmware functions as well as internal radio soldering joints and physical gimbal assembly be carefully checked, before committing a 'cheap' 9X radio controlled aircraft to the skies. SAFETY FIRST!</i></blockquote>

The original <a href='http://code.google.com/p/th9x/'>TH9X project</a> was (and very much still is) about completely replacing the factory supplied operating system in the Turnigy/Eurgle/iMax/Fly-Sky/etc 9X Remote Control transmitter from China -- currently retailing for around USD$40 -- HOW, we do not know!<br>
<br>
From there, other projects then spawned (were forked forked) from TH9X, including ER9X and gruvin9x. More are likely to follow as different interest focuses emerge. In our case, the focus was originally on providing practical Fr-Sky telemetry support and more recently, the design and production of an <a href='PCB.md'>custom controller board</a>, to be a drop-in, upgrade replacement for the stock '9X system controller.<br>
<br>
There's more about gruvin9x on the <a href='About.md'>About</a> wiki page.<br>
<br>
<h3>Documentation</h3>

For G9X hardware or historical information, please consult the <a href='About.md'>project wiki</a> in the first instance, as well as the <a href='http://code.google.com/p/gruvin9x/source/browse/#svn%2Ftrunk%2Fdoc'>doc/ directory</a> in the source tree for all currently available gruvin9x documentation.<br>
<br>
There is also now a growing user maintained wiki documentation project over at <a href='http://9xforums.com'>9xforums.com</a>. The wiki could use <i>your</i> input.  Please consider helping out by providing your own documentation, as you gain familiarity with the related projects.<br>
<br>
<h3>Other '9X OS Replacements</h3>

There's also at least one other project taking on the same basic goal, but of completely different design and unrelated to the TH/ER/gruvin9X projects. It's named Radio Clone, can be found at <a href='http://radioclone.sourceforge.net/'>http://radioclone.sourceforge.net/</a> and is well worth checking out.<br>
<br>
<br>
<h2>Downloading gruvin9x Firmware and Flashing Your Radio</h2>

For details on installing new firmware into you Turnigy/iMax/Eurgle/etc 9X RC Radio, see the <a href='FlashGuide.md'>Flash Guide</a> wiki page.<br>
<br>
<br>
<h2>Getting the gruvin9x Source Code</h2>

See the <a href='CompilingFromSource.md'>Compiling from Source</a> wiki page.<br>
<br>
<br>
<h2>Get Involved!</h2>

An independent group maintain an, 'all things 9X' forum over at <a href='http://9xforums.com/'>9xforums.com</a>. The forum caters to several different firmware projects, has a documentation wiki attached and is probably the most popular hang-out for '9X enthusiasts nowadays.<br>
<br>
There is also the original <a href='http://groups.google.com/group/gruvin9x-discuss'>gruvin9x discussion group</a>. All you need to participate there is a valid Google account.<br>
<br>
To <b>submit bug reports</b> or <b>feature requests</b>, please use the <a href='http://code.google.com/p/gruvin9x/issues'>issues</a> menu link. The issues area lets you log bug reports and make feature requests in an organised and trackable manner. Don't be shy! Give it a go.<br>
<br>
<h2>External Links</h2>

<ul><li><a href='http://code.google.com/p/er9x/'>Original ER9X Project Home</a>
</li><li><a href='http://code.google.com/p/th9x/'>ORIGINAL, Original TH9X Project Home</a> "Respect!" :-D</li></ul>

<ul><li><a href='http://sourceforge.net/apps/mediawiki/radioclone/'>Radio Clone Project</a> -- Something different and well worth checking out.</li></ul>

<ul><li><a href='http://www.rcmodelreviews.com/tendollarbattery.shtml'>$10 Li-Ion Battery Pack Upgrade</a></li></ul>

.<br>
.<br>
.<br>
<br>
<h3>DISCLAIMER</h3>
Whilst the gruvin9x project owner(s) aim to provide as much help to as many Turnigy/iMax/Eurgle/etc '9X users as practical, any perceived enthusiasm on their part to lure people into using gruvin9x over any other version, would be erroneous. This project was originally created primarily for the author's own use -- and of course to 'give back' to the Open Source Community, as the <a href='http://www.gnu.org/licenses/gpl-2.0.html'>GNU General Public License (V2)</a> requests. Anyone is welcome to use this code according to said license, as is, where is and indeed to submit suggestions for changes, improvements, additions, etc. The author welcomes comments, constructive criticism, assistance and general feedback but accepts no responsibility for anything what-so-ever that use of any information contained on this website may or may not be claimed to cause. Use at your own risk. Any opinions offered by this internet resource are expressly, only opinions. (Any information claiming to be fact but not legally verified as fact in actuality, must of course be considered mere opinion, regardless of context.) All care is taken, but no responsibility is accepted for the level of accuracy of any information here or anywhere the author may post text, images, video, audio or other content. Any and all images, photographs, charts, lists or graphical representations of any kind are intended for educational or indicative purposes only and may or may not accurately represent any given subject, topic or fact at any given time. Indeed, any such depictions are subject to change at any time for any reason without notice. Any monetary figures, presented by whatever means, are for indicative, informational or educational purposes only and all such figures are subject to change at any time without notice. The use of sarcasm may or may not feature throughout this internet resource and other, related or linked media, and as such is intended purely as light-hearted humour. No responsibility is accepted for anything what-so-ever relating to perceived truths related to such believed communications. Reader/viewer/listener beware! Any views expressed by individuals other than project owner(s) may or may not agree with the projects goals, intentions or license and no responsibility is taken for any such view or views under any circumstance. Any views so interpreted as being those of the gruvin9x project owner(s) should be taken as potentially inaccurate and with the acceptance that any views, expressed or implied, are at all times subject to change without notice. This disclaimer falls within the above conditions, being itself subject to change at any time without notice. In light of the afore mentioned disclaimers, readers should take heed of the possibility that they may be, a) potentially crazy for reading this far in the first place and, b) that this disclaimer itself, though quite serious, is in part also intended for entertainment purposes. Etc, etc, blah blah. You know the drill. Love and peace to all! Now let's get on with it. :-D