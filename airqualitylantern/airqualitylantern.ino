#define AQTESTINGTIME   60000 // publish air quality every 60s

#define WIFI_SSID       "WIFI_SSID"
#define WIFI_PASSWORD   "WIFI_PASSWORD"

/*
  sign up for an MQTT account:
    https://www.cloudmqtt.com/ or
    https://learn.adafruit.com/adafruit-io/mqtt-api or
    roll your own: http://www.hivemq.com/blog/mqtt-essentials-part-1-introducing-mqtt
*/
#define MQTT_SERVER     "SERVER_ADDRESS"
#define MQTT_USER       "MQTT_USERNAME"
#define MQTT_PASSWORD   "MQTT_PASSWORD"
#define MQTT_TCP_PORT   1883

#define PUBLISHCHANNEL  "lantern/airquality"
#define SUBSCRIBEMODE   "lantern/settings"

//Uncomment this to see additional debugging information
//#define DEBUG_LANTERN   true


//   Do not modify below this line   \\
#include "libs/config.h"
#include "libs/PMS3003A.h"
#include "libs/modes.h"
#include "libs/leds.h"
#include "libs/air_quality_visualizer.h"
#include "libs/connecting_visualizer.h"

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266httpUpdate.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>

unsigned int lanternMode = CONNECTING;

#define VERSION   "1.0.0"
#define TYPE      "lantern"
#define ID        ESP.getChipId()

Config config;
PMS3003A sensor;
Leds leds;
VisualizerAirQuality visualizerAirQuality;
VisualizerConnecting visualizerConnecting;


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output

  #ifdef DEBUG_LANTERN
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  #endif

  config.load();
  setup_PMS();
  leds.setup();
  visualizerAirQuality.setup(sensor, leds, config);
  visualizerConnecting.setup(leds);
  setup_wifi();
  setup_mqtt();
}


void loop() {
  AQ_loop();
  mqtt_loop();
  loop_PMS();

  switch(lanternMode) {
    case CONNECTED:
      visualizerAirQuality.loop();
      break;
    default:
      visualizerConnecting.loop();
  }
}
