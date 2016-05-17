// D5: Software Serial Rx
// D7: Software Serial Tx - dont connect

SoftwareSerial swSer(D5, D7, false, 256);

void setup_PMS() {
  swSer.begin(9600);
}


void loop_PMS() {
  if (swSer.available()) {
    swSer.readBytes(sensor.buf,sensor.len);

    if (sensor.buf[0] == 0x42 && sensor.buf[1] == 0x4d) {
      if (sensor.update()) {
        #ifdef DEBUG_LANTERN
          Serial.print("pm1: \t");
          Serial.print(sensor.pm1);
          Serial.print("\t pm2.5: \t");
          Serial.print(sensor.pm2_5);
          Serial.print("\t pm10: \t");
          Serial.println(sensor.pm10);
        #endif
      }
    } else {
      // discard one more byte
      swSer.readBytes(sensor.buf,1);
    }
  }
}
