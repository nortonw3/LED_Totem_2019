#ifndef FIRE2018_H
#define FIRE2018_H

#include "support.h"




void fire2018() {

  // get one noise value out of a moving noise space
  uint16_t ctrl1 = inoise16(11 * millis(), 0, 0);
  // get another one
  uint16_t ctrl2 = inoise16(13 * millis(), 100000, 100000);
  // average of both to get a more unpredictable curve
  uint16_t  ctrl = ((ctrl1 + ctrl2) / 2);

  // this factor defines the general speed of the heatmap movement
  // high value = high speed
  uint8_t speed = 27;

  // here we define the impact of the wind
  // high factor = a lot of movement to the sides
  x = 3 * ctrl * speed;

  // this is the speed of the upstream itself
  // high factor = fast movement
  y = 15 * millis() * speed;

  // just for ever changing patterns we move through z as well
  z = 3 * millis() * speed ;

  // ...and dynamically scale the complete heatmap for some changes in the
  // size of the heatspots.
  // The speed of change is influenced by the factors in the calculation of ctrl1 & 2 above.
  // The divisor sets the impact of the size-scaling.
  scale_x = ctrl1 / 2;
  scale_y = ctrl2 / 2;

  // Calculate the noise array based on the control parameters.
  uint8_t layer = 0;
  for (uint8_t i = 0; i < Width; i++) {
    uint32_t ioffset = scale_x * (i - CentreX);
    for (uint8_t j = 0; j < Height; j++) {
      uint32_t joffset = scale_y * (j - CentreY);
      uint16_t data = ((inoise16(x + ioffset, y + joffset, z)) + 1);
      noise[i][j] = data >> 8;
    }
  }


  // Draw the first (lowest) line - seed the fire.
  // It could be random pixels or anything else as well.
  for (uint8_t x = 0; x < Width; x++) {
    // draw
    leds[XY(x, Height-1)] = ColorFromPalette( Pal, noise[x][0]);
    // and fill the lowest line of the heatmap, too
    heat[XY(x, Height-1)] = noise[x][0];
  }

  // Copy the heatmap one line up for the scrolling.
  for (uint8_t y = 0; y < Height - 1; y++) {
    for (uint8_t x = 0; x < Width; x++) {
      heat[XY(x, y)] = heat[XY(x, y + 1)];
    }
  }

  // Scale the heatmap values down based on the independent scrolling noise array.
  for (uint8_t y = 0; y < Height - 1; y++) {
    for (uint8_t x = 0; x < Width; x++) {

      // get data from the calculated noise field
      uint8_t dim = noise[x][y];

      // This number is critical
      // If it´s to low (like 1.1) the fire dosn´t go up far enough.
      // If it´s to high (like 3) the fire goes up too high.
      // It depends on the framerate which number is best.
      // If the number is not right you loose the uplifting fire clouds
      // which seperate themself while rising up.
      dim = dim / 1.4;

      dim = 255 - dim;

      // here happens the scaling of the heatmap
      heat[XY(x, y)] = scale8(heat[XY(x, y)] , dim);
    }
  }

  // Now just map the colors based on the heatmap.
  for (uint8_t y = 0; y < Height - 1; y++) {
    for (uint8_t x = 0; x < Width; x++) {
      leds[XY(x, y)] = ColorFromPalette( Pal, heat[XY(x, y)]);
    }
  }

  // Done. Bring it on!
  //FastLED.show();

  // I hate this delay but with 8 bit scaling there is no way arround.
  // If the framerate gets too high the frame by frame scaling doesn´s work anymore.
  // Basically it does but it´s impossible to see then...

  // If you change the framerate here you need to adjust the
  // y speed and the dim divisor, too.
  delay(10);

}

#endif //FIRE2018_H
