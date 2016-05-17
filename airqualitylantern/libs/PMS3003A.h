#ifndef _LANTERN_PMS3003A_H
#define _LANTERN_PMS3003A_H

class PMS3003A {

  public:
    unsigned long pm1 = 0;
    unsigned long pm2_5 = 0;
    unsigned long pm10 = 0;
    unsigned int len = 24;
    char buf[24];
    char update();

  protected:
    char checkValue();
};

#endif