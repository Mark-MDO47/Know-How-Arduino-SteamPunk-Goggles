# Know-How-Arduino-SteamPunk-Goggles

Adapted from two episodes of TWIT-TV Know How
- Episode 186: https://twit.tv/shows/know-how/episodes/186?autostart=false
- Episode 187: https://twit.tv/shows/know-how/episodes/187?autostart=false

![alt text](https://github.com/Mark-MDO47/Know-How-Arduino-SteamPunk-Goggles/blob/master/images/IMG07529_madScience.png "Mad Science is improved when wearing steampunk goggles")
![alt text](https://github.com/Mark-MDO47/Know-How-Arduino-SteamPunk-Goggles/blob/master/images/IMG06760_3goggles.png "Built three steampunk goggles - two for friends")

You can see the various patterns at https://youtu.be/VJ-WH86G7Pg if the mp4 file is too big to play here

Major kudos to Fr. Robert Ballecer and Bryan Burnett for their steampunk goggles project and for pointing me to the FastLED library

Major kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC FastLED library and examples!!!
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

# Goggle Wiring Instructions from TWIT-TV Know How 186:

These are the parts you'll need to order for our Steampunk Goggles Build

[MDO - Note that these prices are from 2016]
1. Vintage Steampunk Welding Goggles    $7.99    
2. GraceAngie 40Pcs Bronze Alloy Roung Clock Watch gears    $6.99    
3. Magnifying Loupe    $6.75    
4. Arduino Nano (Atmega 328P)    $2.19    
5. WS2812 16-Bit RGB LED Ring ($3.17 x 2)    $6.34    
6. 30AWG Silicone Wire ($1.00 x 3) [Red, Black, Blue]    $3.00    
7. 600mah batteries + Charging harness    $18.00    

Total $51.26    
        
You'll also need a 3D Printer that can print the following parts        
Steampunk Googles Frame (Right Side)        
Steampunk Goggles Frame (Left Side)       
Steampunk Goggles LED Holder (x2)        
        
Tools and supplies        
1. 3D Printer        
2. Dremel (or other drilling tool)        
3. Hot Glue Gun        
4. Soldering Kit        
5. Pliers, Screwdrivers        
6. Heat Shrink Tubing (Black)        

Instructions:

1. Disconnect one of the eye cups from the bridge strap
2. Drill a small rat hole at the base of each nose-cutout. (Big enough for 6 strands of 30awg silicone wire
3. Cut the following pieces of 30awg Silicone Wire
-- 2 x 6" Red
-- 1 x 8" Red
-- 2 x 6" Black
-- 1 x 8" Black
-- 1 x 6" White
-- 1 x 8" White
4. Strip and tin all your Silicone wires
6. Cut a 3/4" long piece of 1/4" Black Heat Shrink tubing
7. Run the 3, 8" lengths through the heat shrink tubing, then push the tubing & wires over the exposed bridge strap
8. Reconnect both cups to the bridge strap
9. Run the 3, 8" lengths into the left cup rat-hole.
10. Solder the following:
-- Black to any "GND" pad
-- Red to any "VCC" pad
-- White to "IN" pad
11. Run 1 x 6" black and 1 x 6" red into the left cup rat-hole
12. Solder the following:
-- Black to the remaining "GND" pad
-- Red to the remaining "VCC" pad
13. Solder the black and red wires to a battery connector from the charging harness
14. Pull back the slack wire from the left cup
15. Run the other side of the 8" wires into the rat-hole on the right cup.
16. Solder the following:
-- Black to any "GND" pad
-- Red to any "VCC" pad
-- White to the "OUT" pad
17. Run the remaining 6" black, red and white wires into the right-cup rat-hole.
18. Solder the following:
-- Black to the remaining "GND" pad
-- Red to the remaining "VCC" pad
-- White to the "In" pad
19. Solder the other ends of those wires to the Arduino:
-- Black to "GND"
-- Red to "VIN"
-- White to "D3"

# Goggle Integration Instructions from from TWIT-TV Know How 187:

1. Solder 30awg black/red (ground/voltage) wires to the outside pins of the potentiometer

2. Solder a single 30awg blue or white wire to the inside pin of the pot

3. Solder the black wire to an arduino GND through-hole

4. Solder the red wire to the arduino 5v through-hole

5. Solder the blue/white wire to the arduino Analog 7 through-hole

6. Insulate your Arduino assembly with a strip of 1-1/4" clear heat-shrink.

7. Insert the LED retention rings into each cup, making sure to keep the wires in the cutout

8. Install the potentiometer into the 6mm hole in the right cup, lighing up the support peg with the indent

9. Shave down the center hole of two brass gears so that they will fit around the pot shaft.

10. Place the brass gear over the pot shaft and fasten it with a washer and the mounting nut.

11. Insert the right cup into the right-frame, making sure to line up the bridge strap with the cutout in the frame piece, while holding back the wires so that they'll be hidden by the frame.

12. Using a piece of double-sided foam tape, secure the arduino to the inside of the right frame. 13. Remove the mounting nut, clips and clip spring from the magnifying loupe.

13. Insert the loupe pole through a brass gear, then insert it into the 2mm mounting hole in the left frame.

14. Secure the loupe with the mounting nut, tightening it until the loupe lenses are held in tension.

15. Run the battery harness through the hole at the bottom of the battery plate in the left frame piece.

16. Insert the left cup into the left frame, once again making sure that the wires are covered by the frame. Programming We need to add the code that allows us to use the potentiometer to control which animation is being displayed.

 

Things to Remember

1. We're using the "100 lines" code as the basis of our sketch

2. We soldered the wiper (the pin that sends variable voltage depending on the position of the pot) to Analog 7

3. The data line going to our LED rings is soldered to Digital 3. We have 32 LEDs (16 + 16) [MDO correction pin 3]

 

Things that we changed in the Code

1. DATA_PIN is set to "3"

2. NUM_LEDS is set to "32"

3. Brightness is set to "100"

4. We added "Serial.begin(9600);" to the setup so we can get feedback from the Arduino

5. In "loop()", we changed the last line "EVERY_N_SECONDS( 10 ) { nextPattern();" to: -- "EVERY_N_Seconds ( .5 ) { pattern();" ** By bumping the "EVERY_N_SECONDS" down to .5, it means that the Arduino will call the "pattern()" function ever half-second, instead of checking every 10 seconds ** We're created the function "pattern()" to check the status of the Analog pot and turn it into a value that will set "gCurrentPatternNumber" to a value between 0-5

6. We added a function and an array entry for blanking the ring.

void pattern()

{ int aRead = analogRead(7); // This checks the pot connected to Analong Pin 7 and gives us a value between 0-1024 int PatChoice = map(aRead, 0, 1020, 0, 6); // This maps the value of the pot from 0-1020 to a value between 0-5 Serial.print(aRead); // debug -- Sends the value of the pot to the serial port Serial.print(""\t""); // debug -- Sends a tab Serial.println(PatChoice); // debug -- Sends the remapped value to the serial port, then breaks into a new line gCurrentPatternNumber = PatChoice; // Sent the animation value

}

 
