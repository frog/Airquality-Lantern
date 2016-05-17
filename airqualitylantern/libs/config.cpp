#include "config.h"
#include <FS.h>
#include <ArduinoJson.h>

unsigned long Config::getThreshold() {
  return threshold;
}

void Config::load() {
  load_config();
}
void Config::setThreshold(unsigned long value) {
  threshold = value;
  save_config();
}


boolean Config::init() {
  if (SPIFFS.begin()) {
    return true;
  }
  return false;
}

void Config::save_config() {
  #ifdef DEBUG_LANTERN
  Serial.println("saving config");
  #endif
  if (init()) {

    JsonObject& json = settings.createObject();

    json["threshold"] = threshold;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      #ifdef DEBUG_LANTERN
      Serial.println("failed to open config file for writing");
      #endif
    }

    json.printTo(configFile);
    configFile.close();
  } else {
    #ifdef DEBUG_LANTERN
    Serial.println("failed to open");
    #endif
  }

}
void Config::load_config() {
  if (init()) {
    #ifdef DEBUG_LANTERN
    Serial.println("mounted file system");
    #endif
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      #ifdef DEBUG_LANTERN
      Serial.println("reading config file");
      #endif
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        #ifdef DEBUG_LANTERN
        Serial.println("opened config file");
        #endif
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);

        JsonObject& json = settings.parseObject(buf.get());
        #ifdef DEBUG_LANTERN
        json.printTo(Serial);
        #endif
        if (json.success()) {
          threshold = json["threshold"];
        } else {
          #ifdef DEBUG_LANTERN
          Serial.println("failed to load json config");
          #endif
        }
      }
    }
  } else {
    #ifdef DEBUG_LANTERN
    Serial.println("failed to mount FS");
    #endif
  }
}






