# Know-How-Arduino-SteamPunk-Goggles

adapted from TWIT-TV Know How 187: https://twit.tv/shows/know-how/episodes/187?autostart=false

![alt text](https://github.com/Mark-MDO47/Know-How-Arduino-SteamPunk-Goggles/blob/master/images/IMG07529_madScience.png "Mad Science is improved when wearing steampunk goggles")
![alt text](https://github.com/Mark-MDO47/Know-How-Arduino-SteamPunk-Goggles/blob/master/images/IMG06760_3goggles.png "Built three steampunk goggles - two for friends")

You can see the various patterns at https://youtu.be/5_fy7gLFLTE if the mp4 file is too big to play here

major kudos to Fr. Robert Ballecer and Bryan Burnett for their steampunk goggles project and for pointing me to the FastLED library

major kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC FastLED library and examples!!!
https://github.com/FastLED/FastLED

I made one of the potentiometer-selectable patterns cycle or rove through all the patterns one by one.

Then I noticed the code was originally based on some brilliant FastLED patterns that were designed for linear light strips but of course the goggles use two circular rings.

In particular the “sinelon” pattern seemed like it would benefit from remapping the LEDs in a non-linear order. I made the moving light go in a figure-8 pattern between the goggles.

I added a new racetrack” pattern which does two sinelon “cars” moving at slightly different rates.

I also added a “spinner” pattern with four dots per side that spin, and made one side spin back and forth and the other side spin constantly in one direction.

Finally I looked back at other fantastic code samples from FastLED and adapted the “Fire2012” pattern to two circular rings.
https://github.com/FastLED/FastLED/blob/master/examples/Fire2012WithPalette/Fire2012WithPalette.ino

This code is just for fun; not trying to make it an example of how to code in serious applications.

UPDATE:
See post on TWIT Know-How group in Google Plus: https://plus.google.com/100452347452995185114
See the mention received on TWIT.TV Know-How Episode 225: https://twit.tv/shows/know-how/episodes/225?autostart=false
Thanks Fr. Robert Ballecer and Bryan Burnett for the shout-out!!! Sorry my Google Plus post was such a jaw buster!
