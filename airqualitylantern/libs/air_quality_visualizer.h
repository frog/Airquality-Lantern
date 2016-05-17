#ifndef _LANTERN_AIR_QUALITY_VISUALIZER_H
#define _LANTERN_AIR_QUALITY_VISUALIZER_H

#include "leds.h"
#include "PMS3003A.h"
#include "config.h"

class VisualizerAirQuality {
  public:
    void setup(const PMS3003A &sensor, const Leds &leds, const Config &config);
    void loop();
  private:
    void showRed();
    void showGreen();
    PMS3003A _sensor;
    Leds _leds;
    Config _config;
    bool airIsGood = false;
};

#endif