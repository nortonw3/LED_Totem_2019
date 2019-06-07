#ifndef SUPPORT_H
#define SUPPORT_H

// for matrix animations like fire2018
uint8_t Width  = NUM_STRIPS;
uint8_t Height = NUM_LEDS_PER_STRIP;
uint8_t CentreX =  (Width / 2) - 1;
uint8_t CentreY = (Height / 2) - 1;

// control parameters for the noise array

uint32_t x;
uint32_t y;
uint32_t z;
uint32_t scale_x;
uint32_t scale_y;

// storage for the noise data
// adjust the size to suit your setup
uint8_t noise[16][16];

// heatmap data with the size matrix width * height
uint8_t heat[256];


void show_fps() {
  EVERY_N_MILLIS(100) {
    Serial.println(LEDS.getFPS());
  }
}

// finds the correct index within a non-serpentine matrix
uint8_t XY( uint8_t x, uint8_t y) {
  uint8_t i;
  i = (x * NUM_LEDS_PER_STRIP) + y;
  return i;
}

void clearLEDS() {
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
}

#endif //SUPPORT_H
