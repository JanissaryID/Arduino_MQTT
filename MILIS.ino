void Milis(){
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    ReadSerial();
    previousMillis = currentMillis;   
  }
}

void MilisPush(){
  unsigned long currentMillisPush = millis();
 
  if(currentMillisPush - previousMillisPush > intervalPush) {
    publishMQTT();
//    ReadSerial();
    previousMillisPush = currentMillisPush;   
  }
}

void MilisSendWifiData(){
  unsigned long currentMillisPushWifi = millis();
 
  if(currentMillisPushWifi - previousMillisPushWifi > intervalPushWifi) {
    WriteWifiSerial();
    previousMillisPushWifi = currentMillisPushWifi;   
  }
}

void MilisConnectBroker(){
  unsigned long currentMillisPushWifi = millis();
 
  if(currentMillisPushWifi - previousMillisConnectBroker > intervalConnectBroker) {
    loopConnectBroker();
    previousMillisConnectBroker = currentMillisPushWifi;   
  }
}
