# Ni-Mh vs. Other Power Sources #

**In brief:** Dry-Cell < Alkaline < Ni-MH < Ni-Cd (!) < Li-Fe-PO4 < BEC

It is surprising to see how various types of power cells allow an RC model receiver's operating voltage to dip when moving three servos about. This dip can be _significant_ and even _dangerous_.

Using four alkaline cells, for example, with just a little load on a couple of servos, one can observe receiver voltage dip right down below 4.2 Volts!

This is due to the relatively high internal resistance of such cells.

**Word to the wise:** I certainly wouldn't recommend using alkaline cells to power a 2.4GHz, CPU-utilising receiver in a model air plane!

Shock of horrors! -- It turns out that Ni-Mh cells aren't actually that much better -- especially not the more expensive, longer shelf life versions it seems!

A 4.8V (4S) Ni-Mh pack can readily be made to dip way below 3.6V with only moderate load on three or four servos. This is bad news for RC receivers that will fail or reset when even the shortest, intermittent pulse below about 3.8V occurs. (Think Spektrum DSM2 receivers for just one example -- and just about all modern 2.4GHz, CPU employing receivers not far behind.)

What's the best solution to protect your receiver from possible brownouts under load? In my opinion, that would be either running 2 x Li-Fe-PO4 (A123) cells (make sure your servos can in fact operate above 5V. Not all can!), or doing what electric models do -- use a 7.4V (2S) or 11.1V (3S) Li-Po and a 5V or 6V (S/U)BEC.

In the latter case, assuming your total load is under the stated capabilities of the BEC in question, you will get a (nearly) rock-solid receiver and servo power supply -- right up to maximum stated load. You'll also enjoy better peace of mind and faster, more responsive servos as a bonus.

**So then, another word to the wise:** This is why more and more people are becoming convinced of the merits of moving up to a 5S Ni-Mh pack for their on-board power supply in nitro propelled planes -- or better, as mentioned above.

> _Perhaps surprisingly, as a direct replacement for Ni-Mh cells, modern Ni-Cd cells are actually among the best technology available for low internal resistance and current output current. They're more robust than Li-Ion solutions, though of course also heavier. My point here is that, **just because everyone's using them, doesn't mean that Ni-Mh are necessarily the best**._