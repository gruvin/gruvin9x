# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.

# DIY AoA Sensor Ideas / Notes #

## Links ##

  * http://diydrones.com/forum/topics/angle-of-attack-sensor

  * [Apparently working sensor using magnetic Hall effect sensors and magnets](http://www.charlesriverrc.org/articles/asfwpp/lelke_launch.htm)

> The [9SS series magnetic flux sensor](http://www.honeywell-sensor.com.cn/prodinfo/magnetic_position/installation/p87644_1.pdf) (though they call it a micro switch) used in this project has a magnetic 'input' range of -400 to +400 gauss. Plenty! The output is said to be linearly associated with input gauss, with 0 gauss being at about half the supply voltage -- 8-16V at 15mA (max).

> The AoA design uses two magnets and one Honeywell 9SS-series sensor. No detail seems to be provided as to how the magnet poles should be oriented. I'm guessing that one is configured 180 deg. (north vs. south) to the other, such that as one magnet moves away from the Hall sensor, the other gets closer. That would seem to make sense.


## Random Notes (changes regularly) ##

I dreamt up an idea involving two LDR's (light dependant resistors) with a wedge shaped 'light-blocker' that swings into the light path of one or the other, depending on the AoA. The more light that gets blocks, the higher the resistance becomes. Given a constant internal light source and the two LDR's wired as a resistive divider, this should produce some form of AoA:voltage output. I'm certain it will be anything but linear, no matter how I try to shape the light-path-blocker bit. But it might work. Experimentation is needed.