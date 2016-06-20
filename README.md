# Know-How-Arduino-SteamPunk-Goggles
Modification of the SteamPunk Goggles from TWIT.tv Know-How episode 187

I made one of the potentiometer-selectable patterns cycle or rove through all the patterns one by one.

Then I noticed the code was originally based on some brilliant FastLED patterns that were designed for linear light strips but of course the goggles use two circular rings.

In particular the “sinelon” pattern seemed like it would benefit from remapping the LEDs in a non-linear order. I made the moving light go in a figure-8 pattern between the goggles.

I added a new racetrack” pattern which does two sinelon “cars” moving at slightly different rates.

I also added a “spinner” pattern with four dots per side that spin, and made one side spin back and forth and the other side spin constantly in one direction.

Finally I looked back at other fantastic code samples from FastLED and adapted the “Fire2012” pattern to two circular rings.
