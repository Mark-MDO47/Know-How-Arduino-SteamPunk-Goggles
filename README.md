# Know-How-Arduino-SteamPunk-Goggles

Adapted from two episodes of TWIT-TV Know How
- Episode 186: https://twit.tv/shows/know-how/episodes/186?autostart=false
- Episode 187: https://twit.tv/shows/know-how/episodes/187?autostart=false

**Table Of Contents**

## Pictures
![alt text](https://github.com/Mark-MDO47/Know-How-Arduino-SteamPunk-Goggles/blob/master/images/IMG07529_madScience.png "Mad Science is improved when wearing steampunk goggles")
![alt text](https://github.com/Mark-MDO47/Know-How-Arduino-SteamPunk-Goggles/blob/master/images/IMG06760_3goggles.png "Built three steampunk goggles - two for friends")

## Attribution
Major kudos to Fr. Robert Ballecer and Bryan Burnett for their steampunk goggles project and for pointing me to the FastLED library

Major kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC FastLED library and examples!!!
https://github.com/FastLED/FastLED

## Software changes from KnowHow

You can see a video of the goggles running through all its patterns at https://youtu.be/VJ-WH86G7Pg

I made one of the potentiometer-selectable patterns cycle or rove through all the patterns one by one.

Then I noticed the code was originally based on some brilliant FastLED patterns that were designed for linear light strips but of course the goggles use two circular rings.

In particular the “sinelon” pattern seemed like it would benefit from remapping the LEDs in a non-linear order. I made the moving light go in a figure-8 pattern between the goggles.

I added a new racetrack” pattern which does two sinelon “cars” moving at slightly different rates.

I also added a “spinner” pattern with four dots per side that spin, and made one side spin back and forth and the other side spin constantly in one direction.

Finally I looked back at other fantastic code samples from FastLED and adapted the “Fire2012” pattern to two circular rings.
https://github.com/FastLED/FastLED/blob/master/examples/Fire2012WithPalette/Fire2012WithPalette.ino

This code is just for fun; not trying to make it an example of how to code in serious applications.

## UPDATE:
See post on TWIT Know-How group in Google Plus: https://plus.google.com/100452347452995185114
See the mention received on TWIT.TV Know-How Episode 225: https://twit.tv/shows/know-how/episodes/225?autostart=false
Thanks Fr. Robert Ballecer and Bryan Burnett for the shout-out!!! Sorry my Google Plus post was such a jaw buster!

Later - Google Plus is no more so that link doesn't work

## FURTHER UPDATE:
For a description of differences between the this build and the KnowHow build (other than software changes above), see
* https://github.com/Mark-MDO47/Know-How-Arduino-SteamPunk-Goggles/blob/master/KnowHowBuildInstructions.md

For a schematic-style wiring diagram of this build, see the KiCad directory or
* https://github.com/Mark-MDO47/Know-How-Arduino-SteamPunk-Goggles/blob/master/SteamPunkGoggles_Wiring.pdf
