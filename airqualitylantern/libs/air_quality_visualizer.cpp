#include "air_quality_visualizer.h"
#include <cstring>

void VisualizerAirQuality::setup(const PMS3003A &sensor, const Leds &leds, const Config &config) {
  _sensor = sensor;
  _leds = leds;
  _config = config;
}


void VisualizerAirQuality::loop() {
  airIsGood = _sensor.pm2_5 < _config.getThreshold();

  if (airIsGood) {
    showGreen();
  } else {
    showRed();
  }
}


void VisualizerAirQuality::showRed() {
  _leds.setColor(20, 0, 0);
}


void VisualizerAirQuality::showGreen() {
  _leds.setColor(0, 20, 0);
}
