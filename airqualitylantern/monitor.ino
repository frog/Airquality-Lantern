unsigned long AQlastMsg = 0;

void AQ_loop() {
  unsigned long now = millis();
  
  if (now - AQlastMsg > AQTESTINGTIME) {
    mqtt_send();
    AQlastMsg = now;
  }
}
