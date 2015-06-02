# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.


**NOTE:** Much of this is no longer relevant since incorporating new code to work with self-calibrating band gap reference, which was done to prevent falsely high battery voltage levels when actually below 6v -- when the external ADC reference voltage also starts to fall.

# Why #

Whilst my own Lithium-Ion powered '9X seems fairly stable when taking ADC samples of battery voltage, I've come across several that have considerably more 'jitter' -- especially when powered by relatively high internal resistance cells, like alkaline AA-8-packs for example.

This results in the battery voltage flickering up and down significantly -- in one example, between 8.8V and 9.4V, when a fluke multimeter sat on a steady 9.2V.

Apart from the displeasing visual effect this has for the user, it can also cause annoying intermittent and false low-bat alarms. Not so good.

# The Fix #

Implemented a simple running average -- `new_value = (last_value * 7 + new_sample) / 8`.

The use of 7 'virtual' last values vaguely simulates recording of 7 previous samples and slows down the response to rapidly changing samples -- but is not _too_ slow. This effectively eliminates 'the jitters', where unstable battery voltage samples are occurring, for whatever reason.

## Make Options ##

None. The option to turn this feature off using a `Make` directive was removed some time around [r200](https://code.google.com/p/gruvin9x/source/detail?r=200). Why? Because too many `Make` directives was getting messy and I felt this feature was of benefit to everyone.

# Overflow Bug for Some 8-pack Alkaline Installations #

Interesting fault with new unit. Sample is reading `0x06D0` (around 12.3V) but we're only seeing around 0.2V displayed! (Calibrate = 0)

Long story short, the higher voltage of the new 8-pack of AA alkaline cells I put in the stock'9X, plus just a tiny bit of calibration applied, were causing an overflow in the 16-bit math, causing a wrap-around to a very small voltage. I fixed this, in the end, by changing (improving?) the way I handle calibration.

> READ NO FURTHER, unless you want to waste away some time :-P ...

So, here's an edit of my notes as I worked through this problem ...

The original code comments mention voltage divider resistor values of 5.07K and 2.65K, which I presume must have measured, since the components are marked 502 (5.1K) and 272 (2.7K). My Fluke meter tells me 5.08K and 2.70K for my particular unit. I think we should go with the marked values, using calibration to account for any variances.

So here's me working it out in my slow, half dead brain in the hot, muggy weather of the time ...

> `(2.7+5.1)/2.7*5/1024*1000` -> 14.105V maximum possible reading (assuming perfect resistors and a perfect 5.00V reference.)
> -- therefore, `vbatVolts = 78 * sampleVolts / 27` (tested with sample - 4.27 to yield 12.33V. CORRECT)
> -- therefore, `vbat100mV = 780 * sampleVolts / 27`
> -- where `sampleVolts = sampleValue * 5 / 2048` (because are samples are x2 normalised)
> -- thus `vbat100mV = 780 * sampleValue * 5 / 2048  / 27`
> (Checked with 1744 sample val. to yield 123. CORRECT)

Simplifying that, we come down to...

> `vbat100mV = sampleValue * 3900 / 2048 / 27` (checked)

, therefore

> `vbat100mV = sampleValue * 190 / 2700` (accuracy approx. +/-50mV)

To make the final divide less resource hungry, we'll normalise to an even power of 2. Thus we get,

> `g_vbat100mV = ((uint32_t)ab + 4 * g_eeGeneral.vBatCalib) * 144 / 2048`

Phew! Now onto calibration.

The original code allows adding entire 0.1V steps at each click -- so plus or minus a whopping 12.7V. I don't really need (or like) that, so will likely change it. But first to figure out this overload issue ...

Ah ... the `(ad*35 + ad / 4 * vBatCalib)` in the original code is overflowing on higher voltages if even just one (positive) click of calibration is in effect.

> Example: An input voltage of 12.30V was seen to provide a sample of 1744 (decimal). Thus, `1744*35 + 1744 / 4 * 1 = 76,300` -- more than the 65,535 maximum. Oops.

I originally fixed this by simply type-casting to 32-bit math. But that chews up more RAM than I hoped would be necessary. So I'll keep playing around.

`[Hint: By total fluke, changing the calibration scheme (as below) fixed the problem on its own -- for voltages up to about 13.8V.]`

Moving on then ...

Turns out `vBatCalib` is a signed 8-bit (int8\_t), allowing for values in the range -127 to +127, which if added to the initial sample gives +/-0.89V (after the above math has been applied.) A reasonable calibration range might be +/-3.56V, or in this case +/-(127x4)

Thus, we arrive at `vbat100mV = (sampleValue + 4 x vBatCalib) * 144 / 2048`.

But this still requires 24-bit math for higher voltages, whereas we want to keep within 16-bit. OK then ...

> `g_vbat100mV = ((uint32_t)ab + 4 x g_eeGeneral.vBatCalib) x 36 / 512`

..., which should be good to about 13.8V without overflowing -- including +127 calibration offset to get to that figure. Input voltages above 13.8V _will_ surely still be a problem. But I think I can live with that, in all practicality!

Wow. So, in the end, all I really changed is how the calibration figure affects the final result -- which just happens to have fixed the original overflow issue.

For people who prefer the original system, and who have 7.4V batteries (I guess!), TH's original formula has been reserved and can be used instead by supplying a `-DTHBATVOLTS` command line directive to the compiler.


Some time after the above brain exercise, we added the bandgap reference thing into the mix and I pretty much lost it about there. It took me another day of massive frustration to work out how to make that work to 2 decimal places for calibration (with rounding, I think) and I honestly cannot remember how I did it or how to do it again for these notes. **sigh**