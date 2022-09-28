void initWiFi() {
  digitalWrite(LED, LOW);
  WiFi.begin(WiFiSSID.c_str(), PasswordWifi.c_str());
#if debug
  Serial.print("Connecting to WiFi " + String(WiFiSSID.c_str()));
#endif
  while (WiFi.status() != WL_CONNECTED) {
    Milis();
#if debug
    Serial.print('.');

    delay(1000);
#endif
  }
  statWifi = "1";
#if debug
    Serial.println(WiFi.localIP());
#endif
}

void LedIndicatiorWiFi(){
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    statWifi = "1";
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}
