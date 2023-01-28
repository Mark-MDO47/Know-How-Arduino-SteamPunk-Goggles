# Differences MDO build versus KnowHow build

There are a few differences in my build versus the KnowHow build
- I used a 9V rechargeable battery
- I added a knife switch to power on/off - homage to Frankenstein
- I put all the 5V connections to the Arduino on the 5V pin (no connect for VIN)
- I connected ground to the Arduino REF pin - this gives better performance from the analog input
- I only used one gear for the potentiometer instead of two

Below text is instruction from TWIT-TV KnowHow

# Goggle Wiring Instructions from TWIT-TV Know How 186:

These are the parts you'll need to order for our Steampunk Goggles Build

[MDO - Note that these prices are from 2016]

* Vintage Steampunk Welding Goggles $7.99
* GraceAngie 40Pcs Bronze Alloy Roung Clock Watch gears $6.99
* Magnifying Loupe $6.75
* Arduino Nano (Atmega 328P) $2.19
* WS2812 16-Bit RGB LED Ring ($3.17 x 2) $6.34
* 30AWG Silicone Wire ($1.00 x 3) [Red, Black, Blue] $3.00
* 600mah batteries + Charging harness $18.00

Total $51.26

You'll also need a 3D Printer that can print the following parts
* Steampunk Googles Frame (Right Side)
* Steampunk Goggles Frame (Left Side)
* Steampunk Goggles LED Holder (x2)

Tools and supplies
* 3D Printer
* Dremel (or other drilling tool)
* Hot Glue Gun
* Soldering Kit
* Pliers, Screwdrivers
* Heat Shrink Tubing (Black)

Instructions:
* Disconnect one of the eye cups from the bridge strap
* Drill a small rat hole at the base of each nose-cutout. (Big enough for 6 strands of 30awg silicone wire
* Cut the following pieces of 30awg Silicone Wire -- 2 x 6" Red -- 1 x 8" Red -- 2 x 6" Black -- 1 x 8" Black -- 1 x 6" White -- 1 x 8" White
* Strip and tin all your Silicone wires
* Cut a 3/4" long piece of 1/4" Black Heat Shrink tubing
* Run the 3, 8" lengths through the heat shrink tubing, then push the tubing & wires over the exposed bridge strap
* Reconnect both cups to the bridge strap
* Run the 3, 8" lengths into the left cup rat-hole.
* Solder the following: -- Black to any "GND" pad -- Red to any "VCC" pad -- White to "IN" pad
* Run 1 x 6" black and 1 x 6" red into the left cup rat-hole
* Solder the following: -- Black to the remaining "GND" pad -- Red to the remaining "VCC" pad
* Solder the black and red wires to a battery connector from the charging harness
* Pull back the slack wire from the left cup
* Run the other side of the 8" wires into the rat-hole on the right cup.
* Solder the following: -- Black to any "GND" pad -- Red to any "VCC" pad -- White to the "OUT" pad
* Run the remaining 6" black, red and white wires into the right-cup rat-hole.
* Solder the following: -- Black to the remaining "GND" pad -- Red to the remaining "VCC" pad -- White to the "In" pad
* Solder the other ends of those wires to the Arduino: -- Black to "GND" -- Red to "VIN" -- White to "D3"

# Goggle Integration Instructions from from TWIT-TV Know How 187:

Instructions
* Solder 30awg black/red (ground/voltage) wires to the outside pins of the potentiometer
* Solder a single 30awg blue or white wire to the inside pin of the pot
* Solder the black wire to an arduino GND through-hole
* Solder the red wire to the arduino 5v through-hole
* Solder the blue/white wire to the arduino Analog 7 through-hole
* Insulate your Arduino assembly with a strip of 1-1/4" clear heat-shrink.
* Insert the LED retention rings into each cup, making sure to keep the wires in the cutout
* Install the potentiometer into the 6mm hole in the right cup, lighing up the support peg with the indent
* Shave down the center hole of two brass gears so that they will fit around the pot shaft.
* Place the brass gear over the pot shaft and fasten it with a washer and the mounting nut.
* Insert the right cup into the right-frame, making sure to line up the bridge strap with the cutout in the frame piece, while holding back the wires so that they'll be hidden by the frame.
* Using a piece of double-sided foam tape, secure the arduino to the inside of the right frame. 13. Remove the mounting nut, clips and clip spring from the magnifying loupe.
* Insert the loupe pole through a brass gear, then insert it into the 2mm mounting hole in the left frame.
* Secure the loupe with the mounting nut, tightening it until the loupe lenses are held in tension.
* Run the battery harness through the hole at the bottom of the battery plate in the left frame piece.
* Insert the left cup into the left frame, once again making sure that the wires are covered by the frame. Programming We need to add the code that allows us to use the potentiometer to control which animation is being displayed.

Things to Remember
* We're using the "100 lines" code as the basis of our sketch
* We soldered the wiper (the pin that sends variable voltage depending on the position of the pot) to Analog 7
* The data line going to our LED rings is soldered to Digital 3. We have 32 LEDs (16 + 16) [MDO correction pin 3]

Things that we changed in the Code
* DATA_PIN is set to "3"
* NUM_LEDS is set to "32"
* Brightness is set to "100"
* We added "Serial.begin(9600);" to the setup so we can get feedback from the Arduino
* In "loop()", we changed the last line 
  * "EVERY_N_SECONDS( 10 ) { nextPattern();"
* to: -- 
  * "EVERY_N_Seconds ( .5 ) { pattern();"
* By bumping the "EVERY_N_SECONDS" down to .5, it means that the Arduino will call the "pattern()" function ever half-second, instead of checking every 10 seconds
* We created the function "pattern()" to check the status of the Analog pot and turn it into a value that will set "gCurrentPatternNumber" to a value between 0-5
* We added a function and an array entry for blanking the ring.

The "pattern" routine
* void pattern()
* { int aRead = analogRead(7); // This checks the pot connected to Analong Pin 7 and gives us a value between 0-1024
*   int PatChoice = map(aRead, 0, 1020, 0, 6); // This maps the value of the pot from 0-1020 to a value between 0-5
*   Serial.print(aRead); // debug -- Sends the value of the pot to the serial port
*   Serial.print(""\t""); // debug -- Sends a tab
*   Serial.println(PatChoice); // debug -- Sends the remapped value to the serial port, then breaks into a new line
*   gCurrentPatternNumber = PatChoice; // Sent the animation value
* }
