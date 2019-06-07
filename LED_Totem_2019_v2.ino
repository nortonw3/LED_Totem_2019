
#include <FastLED.h>


#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 255
#define FRAMES_PER_SECOND  120

#define NUM_STRIPS 6
#define NUM_LEDS_PER_STRIP 72
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

#define BUTTON_PIN1 0
#define BUTTON_PIN2 1
int buttonState1 = 0;
int buttonState2 = 0;

// the color palette
CRGBPalette16 Pal;
extern uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() {
  FastLED.addLeds<LED_TYPE, 2, COLOR_ORDER>(leds, 0, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, 14, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, 7, COLOR_ORDER>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, 8, COLOR_ORDER>(leds, 3 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(leds, 4 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, 20, COLOR_ORDER>(leds, 5 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(BRIGHTNESS);
  //FastLED.setDither(DISABLE_DITHER);
  Pal = HeatColors_p;

  pinMode(BUTTON_PIN1, INPUT);
  pinMode(BUTTON_PIN2, INPUT);

  FastLED.delay(3000); // 3 second saftey delay
}

// Include all header files
#include "support.h"
#include "testingAnimations.h"
#include "simpleAnimationsList.h"
#include "fire2018.h"
#include "meatballs.h"

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { juggle, juggle2, stars, stars2, knightRider, knightRider2 };
//SimplePatternList gPatterns = { tornado, strobe };
//SimplePatternList gPatterns = { fire2018, meatballs };
SimplePatternList gPatterns = { stripCheck, fillRed, fillGreen, fillBlue, fillWhite };


uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

// Main Loop
void loop() {
//  buttonState1 = digitalRead(BUTTON_PIN1);
//  buttonState2 = digitalRead(BUTTON_PIN2);
//
//  if (buttonState1 == HIGH) { nextPattern(); }
//  else if (buttonState2 == HIGH) { prevPattern(); }
  
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void prevPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber - 1) % ARRAY_SIZE( gPatterns);
  if (gCurrentPatternNumber < 0) {
    gCurrentPatternNumber = ARRAY_SIZE(gPatterns) - 1;
  }
}
