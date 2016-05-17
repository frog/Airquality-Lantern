
#define MQTT_MAX_PACKET_SIZE  256

char clientID[32];
WiFiClient espClient;
PubSubClient client(espClient);
long lastReconnectAttempt = 0;

boolean reconnect() {
  if (client.connect(clientID, MQTT_USER, MQTT_PASSWORD, "/lwt", 0, 0, "offline")) {
    client.subscribe(SUBSCRIBEMODE);
  }
  return client.connected();
}


void mqtt_loop() {
  if (!client.connected()) {
    lanternMode = CONNECTING;
    long now = millis();

    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    lanternMode = CONNECTED;
    client.loop();
  }
}


void mqtt_send() {
  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["lanternID"] = (long)ID;
  JsonObject& sensorValues = root.createNestedObject("sensorValues");
  sensorValues["pm1"] = sensor.pm1;
  sensorValues["pm2.5"] = sensor.pm2_5;
  sensorValues["pm10"] = sensor.pm10;

  char buffer[256];
  root.printTo(buffer, sizeof(buffer));

  client.publish(PUBLISHCHANNEL, buffer);
}


void callback(char* topic, byte* payload, unsigned int length) {
  char incoming[256];

  for (int i = 0; i < length; i++) {
    incoming[i] = (char) payload[i];
  }

  //assume we will receive a json buffer
  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(incoming);

  const char* lanternID = root["lanternID"];
  unsigned int mode = root["mode"];

  if ((String)topic == (String)SUBSCRIBEMODE && (String)lanternID ==  (String)clientID) {
    if (root["mode"] != NULL) {
      lanternMode = mode;
    }

    if (root["threshold"] != NULL) {
      config.setThreshold(root["threshold"]);
    }
  }
}


void setup_mqtt() {
  ltoa(ID, clientID, 10);
  client.setServer(MQTT_SERVER, MQTT_TCP_PORT);
  client.setCallback(callback);
  lastReconnectAttempt = 0;
}
