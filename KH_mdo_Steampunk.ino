#include "FastLED.h"

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014


// The Fire2012 code is based on 2016-06-01 version of
//   https://github.com/FastLED/FastLED/blob/master/examples/Fire2012WithPalette/Fire2012WithPalette.ino

// Mark Olson 2016-06
// adapted from TWIT-TV Know How 187: https://twit.tv/shows/know-how/episodes/187?autostart=false
//     major kudos to Fr. Robert Ballecer and Bryan Burnett for their steampunk goggles project
//             and for pointing me to the FastLED library
//     major kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC FastLED library and examples!!!
//
// I consider these to be my "mad scientist" goggles...
//
// As in the KH original,  patterns can be selected via the potentiometer. If the potentiometer is set 
//     all the way clockwise, then it "roves" through the patterns (most of them).
// I added a knife-switch on/off control (mad scientist) so I don't use the blank() pattern.
//     Knife switch looks cool!
//
// I adapted the sinelon() pattern to know about the dual-ring LED arrangement; it now does a figure-8
// I added a few patterns; all of them dual-ring aware:
//     racetrack() - like sinelon() but with two non-synchronized "race cars"
//     spinner() - four color spots with RH rotating constant speed and LH rotating back & forth in pattern
//     Fire2012WithPalette() - fire pattern (see Fire2012 above) distributed symmetrically about the nose.
//         When "roving" through the patterns, uses the HEAT color scheme. When pattern statically selected,
//         cycles through color schemes with both sides same scheme (looks better than different schemes).
//         When "roving", both sides move symmetrically around the ring slowly.
//         When pattern statically selected, RH side moves as above but LH side rotating back and forth.

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    32
CRGB leds[NUM_LEDS];

// MDO some more definitions for fancy lights
#define HALF_LEDS (NUM_LEDS/2)
#define QUARTER_LEDS (NUM_LEDS/4)
#define EIGHTH_LEDS  (NUM_LEDS/8)

// MDO analog definitions
#define ANLG_PIN  7
#define ANLG_ROVING 1000 // anything >= this gives the roving pattern

#define BRIGHTNESS         100
#define FRAMES_PER_SECOND  120


#define NUMOF(a) (sizeof((a)) / sizeof(*(a)))

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  80

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 100

CRGBPalette16 gPal_fire;
CRGBPalette16 gPal_fire_alt;

byte g_alt_use_for_lh = 0; // set to 1 to use alt color scheme and mapping for LH

// choose the fire color scheme
#define FIRE_COLOR_SCHEME_HEAT 1 // the FastLED built-in HeatColors_p
#define FIRE_COLOR_SCHEME_BRW  2 // a simplified three-step gradient, from black to red to white
#define FIRE_COLOR_SCHEME_BRYW 3 // a gradient from black to red to yellow to white
#define FIRE_COLOR_SCHEME_BLUE 4 // a similar gradient, but in blue colors rather than red ones
#define FIRE_COLOR_SCHEME_MDO  5 // Mark's attempt to tune fire colors to his LED rings
#define FIRE_COLOR_SCHEME_GRN  6 // Mark's attempt at a green pattern
#define FIRE_COLOR_SCHEME_DYN  7 // a dynamic palette
#define PLAYFIRE_COLOR_SCHEME_MIN  FIRE_COLOR_SCHEME_BRYW // minimum to cycle through
#define PLAYFIRE_COLOR_SCHEME_MAX  FIRE_COLOR_SCHEME_GRN  // maximum to cycle through inclusive
static uint8_t g_color_scheme = FIRE_COLOR_SCHEME_HEAT; // HEAT is used when roving through patterns
static uint8_t g_color_scheme_alt = FIRE_COLOR_SCHEME_BRYW; // alternate scheme for LH side

// #define DEBUG_MAP // print LED mapping on serial monitor each time the arrangement is set
#define DEBUG_POT // print potentiometer setting on serial monitor each time the arrangement is read

// for symmetry of glasses - two round LED strings
// this mapping can be used with the Fire2012 code and with other effects
static byte g_lin2circ_arrange[NUM_LEDS]; // maps linear index to double circle
static byte g_lin2circ_arrange_alt[NUM_LEDS]; // maps linear index to double circle - alternate copy
static byte g_arrange_sym = 1; // 1 = patterns are symmetrical left-to-right and up-to-down
                        // 0 = patterns same side and same top/bottom on both
static char g_arrange_sym_mult = (1-(g_arrange_sym*2)); // -1 for sym, +1 for same)
static int g_arrange_rotate_modulus = 60; // default how many "show()" between rotates;
static int g_arrange_rot_count = 0; // used if we rotate point of fire
static byte g_arrange_rot_rh = 12; // used if we rotate point of fire; map linear 0 to this
                         // 12 means to "nose" of glasses (20 for LH side)
                         //  8 means top of glasses
                         //  4 means outside of glasses
                         //  0 means bottom of glasses
static byte g_arrange_rot_lh = 20; // used if we rotate point of fire
                        // ((g_arrange_rot_rh + HALF_LEDS - g_arrange_sym * QUARTER_LEDS) % HALF_LEDS)
// #define ARRANGE_CAL_RING // display "red" LED on fire point each time the arrangement is set

// example: g_arrange_sym 1 and g_arrange_rot_rh 12 and g_arrange_rot_lh 20
// in this one fire burns from nose of glasses to edges





void setup() {
  delay(3000); // 3 second delay for recovery
  
  Serial.begin(9600);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  // initialize the linear to circular mapping
  init_lin2circ_arrange(g_lin2circ_arrange, g_arrange_rot_lh, g_arrange_rot_rh, g_arrange_sym, g_arrange_sym_mult);

  // initialize the Fire palette
  Fire2012WithPalette_setup(gPal_fire, g_color_scheme);
} // end setup()


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { blank, rainbow, spinner, rainbowWithGlitter, confetti, sinelon, juggle, bpm, Fire2012WithPalette, racetrack };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gRovingPatternNumber = 0; // MDO roving pattern number if roving selected
uint16_t gRovingCount = 0; // MDO roving count to change
uint8_t g_IamRovingThePattern = 0; // MDO - =1 if we are roving the pattern
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 10 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( .5 ) { pattern(); } // change patterns periodically
} // end loop()

void pattern()
{
  int aRead = analogRead(ANLG_PIN); // This checks the pot connected to Analog Pin 7 and gives us a value between 0-1024
  // MDO note: we have on/off switch so don't need zero. Leave in place though
  int PatChoice = map(aRead, 0, ANLG_ROVING, 1, NUMOF(gPatterns)); // This maps the value of the pot from 0-1023 to a value between 1 to last pattern num
  g_IamRovingThePattern = 0;
  if (aRead > (ANLG_ROVING-1)) 
  { // MDO fixes some oscillation at the high end
    g_IamRovingThePattern = 1;
    PatChoice = gRovingPatternNumber + 2;
  }

#ifdef DEBUG_POT
  Serial.print(aRead); // debug -- Sends the value of the pot to the serial port
  Serial.print("\t");  // debug -- Sends a tab
  Serial.println(PatChoice);  // debug -- Sends the remapped value to the serial port, then breaks into a new line
#endif // DEBUG_POT

  gCurrentPatternNumber = PatChoice; // Set the animation value
  rove_pattern();

  // rotate the linear to circular fire points
  loop_lin2circ_arrange();

}  // end pattern()

void rove_pattern() // MDO rove through pattern numbers
{
  gRovingCount += 1;
  if (gRovingCount >=511)
  {
    gRovingCount = 0;
    gRovingPatternNumber = ((gRovingPatternNumber + 1) % (NUMOF(gPatterns)-2)); // MDO +2 to get a pattern
    // rainbow and rainbow with glitter are so close just doing glitter
  }
} // end rove_pattern()

static uint32_t mdoResetTime = 0;

uint32_t mdo_millisecond_timer()
{
  return millis() - mdoResetTime;
} // end mdo_millisecond_timer()

void mdo_millisecond_timer_reset()
{
  mdoResetTime = millis();
} // end mdo_millisecond_timer_reset()

void blank()
{
  fadeToBlackBy( leds, NUM_LEDS, 20); // This gives the goggles an "off" position
} // end blank()

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
} // end rainbow()

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
} // end rainbowWithGlitter()

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
} // end addGlitter()

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
} // end confetti()

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  // Mark Olson 2016-05 - make it do figure-8 by using calcpos_figure8
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,4*NUM_LEDS);
  pos = calcpos_figure8(pos);
  leds[pos] += CHSV( gHue, 255, 192);
} // end sinelon()

// Mark Olson 2016-05
//   racetrack shows two "cars" racing on a figure-8 racetrack
//   The two cars are out of sync with each other so effect appears
//   chaotic (although actually predictable)
void racetrack()
{
  // clear the screen a bit so not too busy
  fadeToBlackBy(leds, NUM_LEDS, 120);
  
  int pos = beatsin16(13,0,4*NUM_LEDS);
  pos = calcpos_figure8(pos);
  leds[pos] += CHSV( gHue, 255, 192);

  pos = beatsin16(14,0,4*NUM_LEDS);
  pos = calcpos_figure8(pos);
  leds[pos] += CHSV( gHue+128, 255, 192);
} // end racetrack()

int calcpos_figure8(int pos)
{
  // Mark Olson 2016-05
  //   tilt both circles 1/4 but in opposite directions
  //   used to make figure 8 for racetrack
  // a different implementation can be found in the routines with lin2circ in the name
  pos %= NUM_LEDS;
  if (pos >= HALF_LEDS) {
    pos = (pos - EIGHTH_LEDS) % HALF_LEDS;
    pos = NUM_LEDS - 1 - pos;
  } else {
    pos =(pos + 3*EIGHTH_LEDS - 1) % HALF_LEDS;
  }
  return(pos);
} // end calcpos_figure8()


static int g_spin_color_mode = 3; // 0=simple, 1=lava, 2=party, 3=party/lava
CRGB spin_colors(byte iter, int led)
{
  // Mark Olson 2016-05
  // used by the spinner routine to cycle through colors
  // I should probably get my act together and merge all the palettes, but I
  //    have not run out of memory yet...
  static CRGB some_spin_colors[4] = { CRGB::White, CRGB::Red, CRGB::Navy, CRGB::Green };
  static CRGBPalette16 party_palette = PartyColors_p;
  static CRGBPalette16 lava_palette = LavaColors_p;

  int my_spin_color_mode = g_spin_color_mode;
  if (my_spin_color_mode >= 3) {
    my_spin_color_mode -= (led/HALF_LEDS) + 1;
  }

  switch (my_spin_color_mode) {
    case 1: // lava
      return ColorFromPalette(lava_palette, gHue-led+(iter*59), led-gHue+(iter*59));
      break;
    case 2: // party
      return ColorFromPalette(party_palette, gHue-led+(iter*59), led-gHue+(iter*59));
      break;

    default:
    case 0: // simple
      return some_spin_colors[iter & 0x3];
      break;
  }
} // end spin_colors()

#define SPIN_INTERVAL 4
void spinner()
{
  // Mark Olson 2016-05
  //   this puts four dots on the screen and spins them
  //   the right hand side goes clockwise at constant speed
  //   the left hand side goes back and forth at varying speed

  // clear the screen a bit so not too busy
  fadeToBlackBy(leds, NUM_LEDS, 100);

  int pos1 = (mdo_millisecond_timer() / 50) & 511;
  int pos2 = beatsin16(13,0,64);

  byte dothue = 0;
  int tmp = 0;
  for (int i = 0; i < HALF_LEDS; i += SPIN_INTERVAL)
  {
     tmp = (pos1+i) % HALF_LEDS;
     leds[tmp] |= spin_colors(dothue, tmp);
     // dothue += 32;
     tmp = (pos2+i+SPIN_INTERVAL/2) % HALF_LEDS;
     tmp = HALF_LEDS-tmp-1; // reverse direction
     leds[tmp+HALF_LEDS] |= spin_colors(dothue, tmp+HALF_LEDS);
     dothue += 1;
  }
} // end spinner()

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
} // end bpm()

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
} // end juggle()

// Linear to Dual-Circular mapping - Mark Olson 2016-06
//
// My LED rings are arranged so that (from the front) LED 0 is on the bottom and the
//    numbering increases as you go clockwise. The right hand ring has numbers 0-15
//    and the left hand ring has numbers 16-31. I take care to make RH 4 match up
//    with LH 20 (both near the nose).
//
// To map the fire simulation linear string to my goggles, the approach is as follows:
//      distribute the fire points between left and right rings. within a ring, distribute
//      points first on one side then the other to cover the ring (for instance) from
//      bottom to top.
//    g_arrange_sym can be 1 (mirror image left-right and top-bottom between the two circles)
//                    or 0 (same geometry for both circles)
//      When the fire point is touching the nose it looks best to have symmetry set to 1.
//         If the fire point is on the bottom, best to have symmetry 0
//         since otherwise on the LH side fire point will be on the top.
//    For the case in which the two fire points on the goggles are at the bottom and symmetry 0:
//      linear 0 (fire bottom) maps to RH bottom (led 0)
//      linear 1 maps to LH bottom (led 16)
//      linear 2 maps to RH bottom off to one side (led 1)
//      linear 3 maps to LH bottom off to one side (led 1)
//      The complete mapping from from linear to dual-circular for start 0 sym 0 is shown here:
//  0 16 1 31 15 17 2 30 14 18 3 29 13 19 4 28 12 20 5 27 11 21 6 26 10 22 7 25 9 23 8 24 
//      The complete mapping from from linear to dual-circular for start 12 sym 1 is shown here:
//  12 20 13 19 11 21 14 18 10 22 15 17 9 23 0 16 8 24 1 31 7 25 2 30 6 26 3 29 5 27 4 28 
//      
//      '#define DEBUG_MAP' to print LED mapping on serial monitor each time the arrangement is set
//      '#define ARRANGE_CAL_RING' to display "red" LED on fire point each time the arrangement is set
void init_lin2circ_arrange(byte * lin2circ_arrange, char arrange_lh, char arrange_rh, char arrange_sym, char arrange_sym_mult)
{
  // This routine initializes an array to account for symmetry of two ring LED strips in glasses
  // un-arranged 12 is approx nose-near for RH side, 20 is approx nose-near for LH side
  byte led;
  static char delta_array[4] = { -1, +1, +1, -1 };

  // if doing rotating point of fire, save current location
  g_arrange_rot_lh = arrange_lh;
  g_arrange_rot_rh = arrange_rh;

  // if NOT calibrating ring, distribute LEDs from linear to dual-circular
#ifndef ARRANGE_CAL_RING
  lin2circ_arrange[0] = arrange_rh % HALF_LEDS;
  lin2circ_arrange[1] = arrange_lh % HALF_LEDS;
  lin2circ_arrange[2] = (lin2circ_arrange[0] + 1) % HALF_LEDS;
  // convert to (int) so can support up to 255 LEDs
  lin2circ_arrange[3] = (HALF_LEDS + ((int) lin2circ_arrange[1]) - 1) % HALF_LEDS;
  for (led = 4; led < NUM_LEDS; led += 1)
  {
    // convert to (int) so can support up to 255 LEDs
    lin2circ_arrange[led] = (HALF_LEDS + (((int) lin2circ_arrange[led-4]) )+ delta_array[led % 4]) % HALF_LEDS;
  }
#else // ARRANGE_CAL_RING - we are calibrating rings; just show fire point
  for (led = 0; led < NUM_LEDS; led += 2)
  {
    lin2circ_arrange[led+0] = arrange_rh % HALF_LEDS;
    lin2circ_arrange[led+1] = arrange_lh % HALF_LEDS;
  }
#endif // ARRANGE_CAL_RING

  // left hand ring has odd-numbered entries
  for (led = 1; led < NUM_LEDS; led += 2)
  {
    lin2circ_arrange[led] += HALF_LEDS; // left-hand side
  }

#ifdef DEBUG_MAP // here to print out our mapping table
  for (led = 0; led < NUM_LEDS; led += 1)
  {
    Serial.print(" ");
    Serial.print(lin2circ_arrange[led]);
  }
  Serial.println(" ");
#endif // DEBUG_MAP
} // end init_lin2circ_arrange()

// Mark Olson 2016-06 - mixed in with playing with fire color scheme rotation
//  this is all a big hack but I haven't gone back to clean it up
void loop_lin2circ_arrange()
{
  // If desired, rotate our point of fire within linear to dual-circular mapping
  // g_arrange_rotate_modulus=1 gives fastest rotation
  // g_arrange_rotate_modulus=0 gives no rotation but still defines the code

  static byte count_rotates = 0; // to slow down color changes
  #define COLOR_CHANGE_FIRE_MODU 5 // change every five moves of fire point (rotates colors around)

  byte my_arrange_rot_rh = g_arrange_rot_rh; // save values so don't overwrite
  byte my_arrange_rot_lh = g_arrange_rot_lh; // save values so don't overwrite
  byte pos_rh = beatsin16(13,0,HALF_LEDS); // 128 is well within 255
  if ((1 == g_alt_use_for_lh) && (pos_rh != g_lin2circ_arrange_alt[0]))
  {
    byte pos_lh = (pos_rh + HALF_LEDS - g_arrange_sym * QUARTER_LEDS) % HALF_LEDS;
    init_lin2circ_arrange(g_lin2circ_arrange_alt, pos_lh, pos_rh, g_arrange_sym, g_arrange_sym_mult);
  }
  g_arrange_rot_rh = my_arrange_rot_rh;
  g_arrange_rot_lh = my_arrange_rot_lh;

  g_arrange_rot_count = (g_arrange_rot_count + 1) % g_arrange_rotate_modulus;
  if (g_arrange_rot_count == 0)
  {
    g_arrange_rot_rh = (g_arrange_rot_rh + 1) % HALF_LEDS;
    g_arrange_rot_lh = (g_arrange_rot_lh + g_arrange_sym_mult + HALF_LEDS) % HALF_LEDS;
    init_lin2circ_arrange(g_lin2circ_arrange, g_arrange_rot_lh, g_arrange_rot_rh, g_arrange_sym, g_arrange_sym_mult);
    count_rotates = (count_rotates + 1) % COLOR_CHANGE_FIRE_MODU;
    if ((0 == g_IamRovingThePattern) && (0 == count_rotates))
    {
      // initialize the Fire palette
      g_color_scheme += 1;
      if (g_color_scheme > PLAYFIRE_COLOR_SCHEME_MAX) { g_color_scheme = PLAYFIRE_COLOR_SCHEME_MIN; }
      Fire2012WithPalette_setup(gPal_fire, g_color_scheme);
      // and for the left-hand side
      g_color_scheme_alt += 1;
      if (g_color_scheme_alt > PLAYFIRE_COLOR_SCHEME_MAX) { g_color_scheme_alt = PLAYFIRE_COLOR_SCHEME_MIN; }
      Fire2012WithPalette_setup(gPal_fire_alt, g_color_scheme_alt);
    }
  }
} // end loop_lin2circ_arrange()


// the work is all done - here we just do the translation
byte getpixnum_lin2circ(byte inpnum)
{
  if ((0 == g_alt_use_for_lh) || (0 == (inpnum & 1)))
  {
    return(g_lin2circ_arrange[inpnum]);
  }
  else
  {
    return(g_lin2circ_arrange_alt[inpnum]);
  }
} // end getpixnum_lin2circ()





// Fire2012 with programmable Color Palette
//
// This code is the same fire simulation as the original "Fire2012",
// but each heat cell's temperature is translated to color through a FastLED
// programmable color palette, instead of through the "HeatColor(...)" function.
//
// Four different static color palettes are provided here, plus one dynamic one.
// 
// The three static ones are: 
//   1. the FastLED built-in HeatColors_p -- this is the default, and it looks
//      pretty much exactly like the original Fire2012.
//
//  To use any of the other palettes below, just "uncomment" the corresponding code.
//
//   2. a gradient from black to red to yellow to white, which is
//      visually similar to the HeatColors_p, and helps to illustrate
//      what the 'heat colors' palette is actually doing,
//   3. a similar gradient, but in blue colors rather than red ones,
//      i.e. from black to blue to aqua to white, which results in
//      an "icy blue" fire effect,
//   4. a simplified three-step gradient, from black to red to white, just to show
//      that these gradients need not have four components; two or
//      three are possible, too, even if they don't look quite as nice for fire.
//
// The dynamic palette shows how you can change the basic 'hue' of the
// color palette every time through the loop, producing "rainbow fire".

void Fire2012WithPalette_setup(CRGBPalette16& palette, byte color_scheme)
{
  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  // NOTE: this switch statement does not include FIRE_COLOR_SCHEME_DYN handled elsewhere
  switch (color_scheme)
  {
    case FIRE_COLOR_SCHEME_HEAT:
      // the built in heat colors
      palette = HeatColors_p;
      break;
    case FIRE_COLOR_SCHEME_BRYW:
      // These are other ways to set up the color palette for the 'fire'.
      // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
      palette = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
      break;
    case FIRE_COLOR_SCHEME_BLUE:
      // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
      palette = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
      break;
    case FIRE_COLOR_SCHEME_BRW:
      // Third, here's a simpler, three-step gradient, from black to red to white
      palette = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
      break;
    case FIRE_COLOR_SCHEME_MDO:
      // MDO attempt to tune for my LEDs
      palette = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::DarkOrange, CRGB::Orange);
      break;
    case FIRE_COLOR_SCHEME_GRN:
      // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
      palette = CRGBPalette16( CRGB::Black, CRGB::Green, CRGB::Aquamarine,  CRGB::White);
      break;
  }
} // end Fire2012WithPalette_setup()



// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
//// 
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//

CRGB get_fire_color(byte color_scheme, uint8_t hue)
{
  CRGB color;
  switch (color_scheme)
  {
    case FIRE_COLOR_SCHEME_DYN:
      color  = CHSV(hue,255,192); // pure hue, three-quarters brightness
      break;
    case FIRE_COLOR_SCHEME_BLUE:
      color = CRGB::Blue;
      break;
    case FIRE_COLOR_SCHEME_GRN:
      color = CRGB::Green;
      break;
    default:
      color = CRGB::Red;
      break;
  }
  return(color);
}


void Fire2012WithPalette()
{
  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];
  static CRGB color;
  static uint8_t hue = 0;
  static byte pixpos = 0;

  // Mark Olson 2016 - add a little chaos
  mdoWantsToPlayWithFire();
  
  // Finally, the most sophisticated: this one sets up a new palette every
  // time through the loop, based on a hue that changes every time.
  // The palette is a gradient from black, to a dark color based on the hue,
  // to a light color based on the hue, to white.
  //
  if (g_color_scheme == FIRE_COLOR_SCHEME_DYN)
  {
    hue += 1;
    CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
    CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
    gPal_fire = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);
  }
  
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());

  // Step 1.  Cool down every cell a little
    for( byte i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( byte k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( byte j = 0; j < NUM_LEDS; j++) {
      // Scale the heat value from 0-255 down (original 0-240 but I like 140)
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 140);
      
      // Mark Olson: below is a big hack and all my fault, but I haven't gone back to clean it up
      //    I was playing with fire...
      pixpos = getpixnum_lin2circ(j);
      if (g_alt_use_for_lh && (pixpos >= HALF_LEDS))
      {
        color = ColorFromPalette(gPal_fire_alt, colorindex);        
      }
      else
      {
        color = ColorFromPalette(gPal_fire, colorindex);        
      }
      leds[pixpos] = color;
    }

    // Step 5. Put a "RED" spot on the two fire points
    for( byte j = 0; j < 2; j++) {
      pixpos = getpixnum_lin2circ(j);
      if (g_alt_use_for_lh && (pixpos >= HALF_LEDS))
      {
        color = get_fire_color(g_color_scheme_alt, hue);        
      }
      else
      {
        color = get_fire_color(g_color_scheme, hue);        
      }
      leds[pixpos] = color;
    }
}  // end Fire2012WithPalette()

// Mark Olson 2016-06
//   OK - the Fire2012 stuff is awesome!!!        but I like a little chaos...
//   When g_IamRovingThePattern is 1: we will do HEAT and symmetric and synchronized rotation
//      because we only have a few seconds to display our pattern
//   When g_IamRovingThePattern is 0: we will mix throught the color and maybe do wierd stuff
//      with the rotation...
//  this is all a big hack but I haven't gone back to clean it up
void mdoWantsToPlayWithFire()
{
  if (1 == g_IamRovingThePattern)
  {
    if (FIRE_COLOR_SCHEME_HEAT != g_color_scheme)
    {
      g_alt_use_for_lh = 0; // same scheme both sides

      // initialize the Fire palette
      g_color_scheme = FIRE_COLOR_SCHEME_HEAT;
      Fire2012WithPalette_setup(gPal_fire, g_color_scheme);
    }
  }
  else
  {
    if ((g_color_scheme < PLAYFIRE_COLOR_SCHEME_MIN)
       || (g_color_scheme > PLAYFIRE_COLOR_SCHEME_MAX))
    {
      // initialize the Fire palette
      g_color_scheme = PLAYFIRE_COLOR_SCHEME_MIN;
      Fire2012WithPalette_setup(gPal_fire, g_color_scheme);
      // and for the left-hand side
      g_color_scheme_alt = PLAYFIRE_COLOR_SCHEME_MIN; // being different made it look wierd
      Fire2012WithPalette_setup(gPal_fire_alt, g_color_scheme_alt);
    }
    g_alt_use_for_lh = 1; // different scheme each sides
  }
} // end mdoWantsToPlayWithFire()

