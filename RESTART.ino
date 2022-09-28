void restartESP(String myssid, String password){
  if(statRestart == "1"){
#if debug
    Serial.print("SSID = ");
    Serial.println(myssid);

    Serial.print("PASSWORD = ");
    Serial.println(password);
#endif
    writeStringToEEPROM(40, myssid);
    writeStringToEEPROM(70, password);

    ESP.restart();
  }
}
