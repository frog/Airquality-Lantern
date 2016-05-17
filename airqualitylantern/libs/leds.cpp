#include "leds.h"
#include <NeoPixelBus.h>



void Leds::setup() {
  leds = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(NUMBER_OF_PIXELS, LED_PIN);
  leds->Begin();
  leds->Show();
}

void Leds::setColor(unsigned int r, unsigned int g, unsigned int b) {
  if (rgb[0] == r && rgb[1] == g && rgb[2] == b) return;

  RgbColor newColor(r, g, b);
  for(int i=0;i<NUMBER_OF_PIXELS;i++){
    leds->SetPixelColor(i, newColor);
  }

  leds->Show();

  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;

}

