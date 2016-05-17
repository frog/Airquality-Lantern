#ifndef _LANTERN_LEDS_H
#define _LANTERN_LEDS_H

#include <NeoPixelBus.h>
#define NUMBER_OF_PIXELS  24
#define LED_PIN           D6//this is ignored


class Leds {
  public:
    void setup();
    void setColor(unsigned int r, unsigned int g, unsigned int b);

  private:
    unsigned int rgb[3] = {0, 0, 0};
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *leds = NULL;

};

#endif