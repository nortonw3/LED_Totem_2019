#ifndef MEATBALLS_H
#define MEATBALLS_H

#include "support.h"

void CLS() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = 0x000000;
  }
}

void MetaBalls() {

  float speed = 1;

  // get some 2 random moving points
  uint8_t x2 = inoise8(millis() * speed, 25355, 685 ) / 16;
  uint8_t y2 = inoise8(millis() * speed, 355, 11685 ) / 16;

  uint8_t x3 = inoise8(millis() * speed, 55355, 6685 ) / 16;
  uint8_t y3 = inoise8(millis() * speed, 25355, 22685 ) / 16;

  // and one Lissajou function
  uint8_t x1 = beatsin8(23 * speed, 0, 15);
  uint8_t y1 = beatsin8(28 * speed, 0, 15);

  for (uint8_t y = 0; y < Height; y++) {
    for (uint8_t x = 0; x < Width; x++) {

      // calculate distances of the 3 points from actual pixel
      // and add them together with weightening
      uint8_t  dx =  abs(x - x1);
      uint8_t  dy =  abs(y - y1);
      uint8_t dist = 2 * sqrt((dx * dx) + (dy * dy));

      dx =  abs(x - x2);
      dy =  abs(y - y2);
      dist += sqrt((dx * dx) + (dy * dy));

      dx =  abs(x - x3);
      dy =  abs(y - y3);
      dist += sqrt((dx * dx) + (dy * dy));

      // inverse result
      byte color = 1000 / dist;

      // map color between thresholds
      if (color > 0 and color < 60) {
        leds[XY(x, y)] = CHSV(color * 9, 255, 255);
      } else {
        leds[XY(x, y)] = CHSV(0, 255, 255);
      }
        // show the 3 points, too
        leds[XY(x1,y1)] = CRGB(255, 255,255);
        leds[XY(x2,y2)] = CRGB(255, 255,255);
        leds[XY(x3,y3)] = CRGB(255, 255,255);
    }
  }



  //FastLED.show();
  //CLS();


}

#endif //MEATBALLS_H
