void setup_wifi() {
  delay(10);
  
  // We start by connecting to a WiFi network
  #ifdef DEBUG_LANTERN
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  #endif
  
  // WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  lanternMode = CONNECTING;
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
    #ifdef DEBUG_LANTERN
    Serial.print(".");
    #endif  
  }
  
  lanternMode = CONNECTED;
  
  #ifdef DEBUG_LANTERN
  Serial.println();
  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
  #endif
}
