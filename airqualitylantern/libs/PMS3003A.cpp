#include "PMS3003A.h"

char PMS3003A::update() {
  return checkValue();
}

char PMS3003A::checkValue() {
  char receiveflag=0;
  int receiveSum=0;
  char i=0;

  for(i=0;i<len;i++) {
    receiveSum=receiveSum+buf[i];
  }

  if(receiveSum==((buf[len-2]<<8)+buf[len-1]+buf[len-2]+buf[len-1])) {
    receiveSum=0;
    receiveflag=1;
    pm1=((buf[4]<<8) + buf[5]); //count PM1.0 value of the air detector module
    pm2_5=((buf[6]<<8) + buf[7]);//count PM2.5 value of the air detector module
    pm10=((buf[8]<<8) + buf[9]); //count PM10 value of the air detector module
  }
  return receiveflag;
}

