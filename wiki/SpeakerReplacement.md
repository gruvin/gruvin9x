# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.


# Replacing the Stock Beeper with a Speaker #

## Why? ##

One could easily wonder why beeps and buzzes are so important that I had to write a bunch of code and change my hardware for it. Well, let me explain my motives ...

<img src='http://gruvin9x.googlecode.com/svn/wiki/SpeakerReplacement.attach/lri.jpg' align='right' width='160'> Aside from replicating features found on other brand radios, such as low/mid/high point trim tones and the like, the one thing I have always most wanted from telemetry is an AoA (<a href='http://en.wikipedia.org/wiki/Angle_of_attack'>Angle of Attack</a>) instrument. What's an AoA instrument? ... Well in short, it's used to assist in landing and as I understand it, is usually calibrated as a Lift Reserve Indicator or LRI.<br>
<br>
AoA or LRI is an analogue feedback device, intended to be superior to the basic stall warning. Many argue that's it's completely redundant and that we've got along fine for years without it. However, I'm not one of them and this project is not about full-size air craft anyway.<br>
<br>
Now, I am perfectly capable of putting most any plane down like a feather just visually from my years of experience to date. And I no longer care much for stall warning switches or airspeed indication, as I've come to doubt such would really help much in practice, if at all. Never the less, at this stage, I still believe that appropriately configured audio LRI feedback could at least be fun, if not reassuring. It should not even need much calibration, since our ears/brain will remember what sounds 'about right', near the point of minimum lift reserve, after a just a few landings.<br>
<br>
<h2>How?</h2>

Some kind of AoA sensor will be added to an available model plane, in at least the 40-size category. Fr-Sky telemetry will be used to send data back to my custom '9X radio.<br>
<br>
What I plan is to use varying pitch tones, similar to the sensitive rise/sink tones from a modern sail plane variometer. Typically, sink comes across as a constant, relatively low tone, falling more in pitch as the sink is greater. Rise is usually an intermittent "bip bip bip" tone, rising in pitch and frequency as lift increases. The sounds are very intuitive and allow you to know exactly what's going on without staring at an instrument panel. Of course, my tones will aim to indicate relative angle-of-attack or lift reserve, not rise/sink.<br>
<br>
With that, and a suitably functional AoA sensor on my aircraft (and that's a whole other story!) ... I should be able to gauge an appropriate landing approach for the plane with more certainty. In general of course, my own eyes and brain can do this pretty well, most of the time.<br>
<br>
Now, if you fly on a relatively flat chunk of land somewhere, you might be wondering what this is really all about. Well, I/we don't have such luxuries around here. One of the fields (especially) that I frequent is located in an undulated area of varying ground types, including water. One experiences a multitude of essentially unpredictable lift, sink, rotor and general turbulence, often on final approach. We cope with it all perfectly well without fancy AoA gadgets of course. But that's besides the point. :-D<br>
<br>
Now, I don't know if, in practice, any LRI feedback system of my own design will be accurate or responsive enough, or even help much at all for that matter. But I do want to find out. Will it make my landings any better and will anyone else even care? Well, maybe not. But I'm going to have fun making it all happen. That much is certain.<br>
<br>
<br>
<h2>Speaker Installation</h2>

Below is an image showing the first ugly speaker install I did. Hey! It works mmmkay? :-P Later I'll probably add some resistor and another capacitor or two to smooth out the square wave for a nicer tone.<br>
<br>
<img src='http://gruvin9x.googlecode.com/svn/wiki/SpeakerReplacement.attach/spkr-install.jpg' />

<h2>Results to Date</h2>

As of gruvin9x <a href='https://code.google.com/p/gruvin9x/source/detail?r=46'>r46</a>, all trim switches and general +/- keypad operations have lower/mid/higher tone for down/reached-zero/up value inputs respectively. The tones are much more pleasant to the ear (IMHO) than the stock internal beeper. (I have since also noted that different batches of these '9X radios can have significantly different sounding beepers. Some of them aren't actually that bad. Mine was truly horrid. :-/)