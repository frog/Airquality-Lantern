#ifndef _LANTERN_CONFIG_H
#define _LANTERN_CONFIG_H


#include <FS.h>
#include <ArduinoJson.h>
class Config {
  public:

    unsigned long getThreshold();
    void load();
    void setThreshold(unsigned long value);

  private:
    DynamicJsonBuffer settings;
    unsigned long threshold = 30;

    boolean init();

    void save_config();
    void load_config();
};

#endif

