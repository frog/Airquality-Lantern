#ifndef _LANTERN_CONNECTING_VISUALIZER_H
#define _LANTERN_CONNECTING_VISUALIZER_H

#include "leds.h"


class VisualizerConnecting {
  public:
    void setup(const Leds& leds);
    void loop();
  private:
    void off();
    void on();
    Leds _leds;
    bool blinking = false;
    unsigned long last = 0;
};

#endif