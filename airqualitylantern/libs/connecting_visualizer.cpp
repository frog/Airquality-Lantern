#include "connecting_visualizer.h"

void VisualizerConnecting::setup(const Leds& leds) {
  _leds = leds;
}


void VisualizerConnecting::loop() {
  unsigned long now = millis();
  
  if (now - last > 500) {
    last = now;
    blinking =!blinking;
  }

  if (blinking) {
    off();
  } else {
    on();
  }
}


void VisualizerConnecting::off() {
  _leds.setColor(0,0,0);
}


void VisualizerConnecting::on() {
  _leds.setColor(20,20,20);
}


