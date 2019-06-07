#ifndef SIMPLEANIMATIONSLIST_H
#define SIMPLEANIMATIONSLIST_H

void juggle() {
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for(int i = 0; i < NUM_STRIPS; i++) {
    leds[(i*NUM_LEDS_PER_STRIP) + beatsin16(i + 7, 0, NUM_LEDS_PER_STRIP-1)] |= CHSV(dothue, 200, 255);
      
    dothue += 32;
  }
}

void juggle2() {
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16( i + 7, 0, NUM_LEDS_PER_STRIP - 1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void sinlon() {
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin16(30, 0, NUM_LEDS);
  static int prevpos = 0;
  if (pos  < prevpos) {
    fill_solid(leds+pos, (prevpos-pos)+1, CHSV(gHue, 220, 255));
  } else {
    fill_solid(leds+prevpos, (pos-prevpos)+1, CHSV(gHue, 220, 255));
  }
  prevpos=pos;
}

void stars() {
  int randVal = 50;
  fadeToBlackBy(leds, NUM_LEDS, 20);
  for(int i = 0; i < NUM_STRIPS; i++) {
    if( random8() < randVal) {
    leds[(i*NUM_LEDS_PER_STRIP) + random16(NUM_LEDS_PER_STRIP) ] += CRGB::White;
    }
  }
}

void stars2() {
  int randVal = 1000;
  fadeToBlackBy(leds, NUM_LEDS, 50);
  for(int i = 0; i < NUM_STRIPS; i++) {
    if( random8() < randVal) {
    leds[(i*NUM_LEDS_PER_STRIP) + random16(NUM_LEDS_PER_STRIP) ] += CRGB::White;
    }
  }
}

void knightRider() {  // 110, 30
  fadeToBlackBy(leds, NUM_LEDS, 90);
  for(int i = 0; i < NUM_STRIPS; i++) {
    int pos = beatsin16(30, 0, NUM_LEDS_PER_STRIP - 1);
    leds[(i*NUM_LEDS_PER_STRIP) + pos] = CRGB::Red;
   }     
}

void knightRider2() {  // 110, 30
  fadeToBlackBy(leds, NUM_LEDS, 90);
  for(int i = 0; i < NUM_STRIPS; i++) {
    int pos = beatsin16(30, 0, NUM_LEDS_PER_STRIP - 1);
    leds[(i*NUM_LEDS_PER_STRIP) + pos] = CRGB::DeepPink;
   }     
}

void tornado() {
  fadeToBlackBy(leds, NUM_LEDS, 20);
  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    for (int j = 0; i < NUM_STRIPS; j++) {
      leds[XY(j, i)] |= CHSV(gHue, 220, 255);
      FastLED.delay(10);
    }
  }
}

void strobe() {
  int randVal = 10;
  int i = random8(0, 5);
  fadeToBlackBy(leds, NUM_LEDS, 20);
  if (random8() < randVal) {
    fill_solid(leds + (i * NUM_LEDS_PER_STRIP), NUM_LEDS_PER_STRIP, CRGB::White);
  }
}

#endif
