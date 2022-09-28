void connectMqttBroker(){
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  // while (!client.connected()) {
  //   String client_id = "PLD32TV1855 - ";
  //   client_id += String(WiFi.macAddress());
  //   Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
  //   if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
  //     Serial.println("Connected to Broker");
  //   } else {
  //     Serial.print("failed with state ");
  //     Serial.print(client.state());
  //     delay(2000);
  //   }
  // }

  loopConnectBroker();

  subscribeData();
}

void loopConnectBroker(){
  while (!client.connected()) {
    String client_id = "PLD32TV1855 - ";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connected to Broker");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void callback(char *topic_remote, byte *payload, unsigned int length) {
  String dataJson;
  // Serial.print("Message arrived in topic: ");
  // Serial.println(topic_remote);
  // Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    dataJson += (char) payload[i];
      // Serial.print((char) payload[i]);
  }
  decodeJson(dataJson);
  // Serial.println(dataJson);
  // Serial.println("-----------------------");
  dataJson = "";
}

void decodeJson(String JsonData){
  StaticJsonDocument<200> doc;

  int str_len = JsonData.length() + 1;
  char char_array[str_len];

  JsonData.toCharArray(char_array, str_len);

  // Serial.println(char_array);

  DeserializationError error = deserializeJson(doc, char_array);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  const char* id = doc["ID"];
  const int key = doc["Key"];

  // Serial.println(id);
  // Serial.println(key);

  sendCommand(key, id);
}

void publishMQTT(){

    String sumData, swV1, swV2, swV3, chnl, macAddressTv, project;

    if((String(dataTvStringInt.Freq)).length() > 6){
      sumData = String('-') + 
      "#" + String('-') + 
      "#" + String('-') + 
      "#" + String('-') +
      "#" + String('-') + "#"
      ;

      swV1 = String('-');
      swV2 = String('-');
      swV3 = String('-');
      chnl = String('-');
      project = String('-');
      macAddressTv = String(dataTvString.macAddressTV);
    }
    else{
      sumData = String(dataTvStringInt.Freq) + 
      "#" + String(dataTvStringInt.Post) + 
      "#" + String(dataTvStringInt.Picture) + 
      "#" + String(dataTvStringInt.Sound) +
      "#" + String(dataTvStringInt.Time) + "#"
      ;

      swV1 = String(dataTvString.swVersion1);
      swV2 = String(dataTvString.swVersion2);
      swV3 = String(dataTvString.swVersion3);
      chnl = String(dataTvString.channelTv);
      project = String(dataTvString.projectVersion);
      macAddressTv = String(dataTvString.macAddressTV);
    }

    sendDataToServer(sumData, swV1, swV2, swV3, chnl, macAddressTv, project);
  
    // Publish and print data
    // antares.publish(projectName, deviceNamePush);
    publishData();
}

void sendDataToServer(String sumData, String swV1, String swV2, String swV3, String chnl, String macAddressTv, String project){
    addData("Data", sumData);
    addData("#Sw1", swV1);
    addData("#Sw2", swV2);
    addData("#Sw3", swV3);
    addData("#ch1", chnl);
    addData("#prj", project);
    addData("#mac", macAddressTv);
    addData("#ID", StringID);

    ClearData();
}

void addData(String Key, String Data){
  doc[Key] = Data;
}

void publishData(){
  char buffer[256];
  serializeJson(doc, buffer);
  // Serial.println(serializeJson(doc, buffer));
  client.publish(topic, buffer);
}

void subscribeData(){
  client.subscribe(topic_remote);
}