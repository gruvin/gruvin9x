# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.


# G9X FAQ #
<b>F</b>requently <b>A</b>sked <b>Q</b>uestions


---


**Q.** **How do I delete a DR/EXPO, MIXER line or model?**

**A.** Click `[MENU]` once on the line/model you want to delete, so that is becomes 'selected', as if you were going to copy or move it. Then, while it is still selected, press `[EXIT LONG]`.

This same procedure should work for deleting lines in all similar menus. In the models menu, you get an 'Are you sure?' type pop-up, for extra safety.

NOTE: You cannot delete the currently active model. (It's a safety feature.)


---


**Q.** **Is there a support forum for gruvin9x?**

**A.** No and there never will be. But there is a [gruvin9x email list](http://groups.google.com/group/gruvin9x-discuss) hosted by Google Groups.

The reason for no forum is that we intend to create a structured,  online help section using the project wiki -- as well as a PDF user manual, which we believe will be hugely more efficient for the intended purpose.


---


**Q.** **Where is the updated PDF user manual for gruvin9x?**

**A.** It's still under development. No time frame for a first edition is yet known.

In the mean time, please refer to this FAQ or consult the members of the gruvin9x Google discussion group (email <i>gruvin9x-discuss</i> `[at]` <i>google</i>`[delete_no_spam]`<i>groups.com</i>) for answers to any mysteries.

As a filler or for different wording on the same topic of how the multiplexing mixer stuff works you could refer to [this forum post](http://www.parkflyers.org.nz/modules/newbb/viewtopic.php?post_id=48056#forumpost48056) (by Gruvin). Skip past the heli-setup part.


---


**Q.** **How do I calibrate the '9X battery voltage reading? It's reading half a volt or more off what it should!**

**A.** Some variance from radio to radio in this respect is normal and to be expected. Just like the sticks and pot's, **you need to calibrate the battery voltage reading**.

On the ANA screen -- in the set-up menus accessed from `[LEFT long]` -- if you press `[DOWN]`, you'll end up at the battery voltage (not labelled so) down the bottom of the screen. You can then adjust the value up and down to have it match what your volt meter says the battery voltage really is.

It's a good idea to take a backup of the EEPROM (which includes this calibration setting) straight away. If you're using eePe or companion9x for model configuration etc, then you should take care to use this most recent backup as the base for all your future EEPROM data. If in doubt later on, get your volt meter out and check the calibration again.


---


**Q.** **How to use the Telemetry A1/2. It's Confusing!**

**A.** Yes, it is confusing. We're working on it, slowly. There's no offset capability however (for going down into negative numbers.)

We intend changing to the simple system currently used by the open9x project, where MaxV etc are replaced by just two fields, "Range" and "Offset".

So for example, if you had a gadget that converts Km/h wind speed over a range of zero to 100Km/hr, to a voltage between 0V and 3.3V, then you'd simply set the range to 100 and offset to 0.

Another example could be temperature, where the sensor might out voltage from 0V to 3.3V over the range -20C to +80C. This would equate to a settings of range = 100 with an offset = -20.


---

