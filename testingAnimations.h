#ifndef TESTINGANIMATIONS_H
#define TESTINGANIMATIONS_H

#include "support.h"

void stripCheck() {
   for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = 0; j <= i; j++) {
      leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB::Red;
    }
  }
}

void fillRed() {
  fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0));
}

void fillGreen() {
  fill_solid(leds, NUM_LEDS, CRGB(0, 255, 0));
}

void fillBlue() {
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 255));
}

void fillWhite() {
  fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
}

#endif //TESTINGANIMATIONS_H
