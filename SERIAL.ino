//Fungsi untuk membaca serial dari TV
void ProcessDataSerialTv(String myData, int index){
  int lenData;
  uint16_t Time;

  int countBreak = 0;

  struct myDataTv dataTv;
//  struct myDataTvString dataTvString;
  
  // read the incoming byte:
  lenData = myData.length();

  String stringData = "";

  

  switch (index) {
    case 0:
      dataTvStringInt.Freq = 0;
      // myFreq = 0;
      
      dataTvStringInt.Freq += myData[0] << 24;
      dataTvStringInt.Freq += myData[1] << 16;
      dataTvStringInt.Freq += myData[2] << 8;
      if(myData[3] != 0){
        dataTvStringInt.Freq += myData[3];
      }
      else{
        dataTvStringInt.Freq = dataTvStringInt.Freq >> 8;
      }

//      Serial.print("Freq = ");
//      Serial.println(dataTv.Freq);
      // myFreq = dataTv.Freq;
      break;
    case 1:
      dataTvStringInt.Post = 0;
      // myPost = 0;
      
      dataTvStringInt.Post += myData[0] << 24;
      dataTvStringInt.Post += myData[1] << 16;
      if(myData[2] != 0){
        dataTvStringInt.Post += myData[2] << 8;
      }
      else{
        dataTvStringInt.Post = dataTvStringInt.Post >> 8;
      }

      if(myData[3] != 0){
        dataTvStringInt.Post += myData[3];
      }
      else{
        dataTvStringInt.Post = dataTvStringInt.Post >> 8;
      }

//      Serial.print("Post = ");
//      Serial.println(dataTv.Post);
      // myPost = dataTv.Post;
      break;
    case 2:
      dataTvStringInt.Picture = 0;
      // myPic = 0;
      
      dataTvStringInt.Picture += myData[0] << 8;
      dataTvStringInt.Picture += myData[1];

//      Serial.print("Picture = ");
//      Serial.println(dataTv.Picture);
      // myPic = dataTv.Picture;
      break;
    case 3:
      dataTvStringInt.Sound = 0;
      // mySound = 0;
      
      dataTvStringInt.Sound += myData[0] << 8;
      dataTvStringInt.Sound += myData[1];

//      Serial.print("Sound = ");
//      Serial.println(dataTv.Sound);
      // mySound = dataTv.Sound;

      
      break;
    case 4:
      dataTvStringInt.Time = 0;
      // myTime = 0;
      
      dataTvStringInt.Time += myData[0] << 8;
      if(myData[1] != 0){
        dataTvStringInt.Time += myData[1];
      }
      else{
        dataTvStringInt.Time = dataTvStringInt.Time >> 8;
      }

//      Serial.print("Time = ");
//      Serial.println(dataTv.Time);
      // myTime = dataTv.Time;
      
      break;
    case 5:
      for(int a = 1; a <= myData.length()+1 ;a++){
        stringData += myData[a];
      }
      SplitStringSW(stringData);
      
      
      break;
    case 6:
        for(int a = 0; a <= myData.length()+1 ;a++){
          if(myData[a] == 0){
            break;
          }
          else{
            dataTvString.channelTv += myData[a];
          }
        }

//      Serial.print("Channel = ");
//      Serial.println(dataTvString.channelTv);
      
      break;
    case 7:
      for(int a = 0; a <= myData.length()-1 ;a++){
        dataTvString.projectVersion += myData[a];
      }
      
//      Serial.print("Project Version = ");
//      Serial.println(dataTvString.projectVersion);
      break;

    case 8:
      for(int a = 0; a <= myData.length()+1 ;a++){
        dataTvWifi.mySSID += myData[a];
      }

//      Serial.print("SSID = ");
//      Serial.println(dataTvWifi.mySSID);
      break;
    case 9:
      for(int a = 0; a <= myData.length()+1 ;a++){
        dataTvWifi.myPassword += myData[a];
      }

//      Serial.print("Password = ");
//      Serial.println(dataTvWifi.myPassword);
      break;
    case 10:
      statRestart = myData[0];
//      Serial.print("Stat Restart = ");
//      Serial.println(statRestart);
      restartESP(dataTvWifi.mySSID, dataTvWifi.myPassword);
      break;
    default:
      break;
  }
  
  dataTvString.macAddressTV = WiFi.macAddress();

  if(index == 10){
    WriteWifiSerial();
    
    if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
      MilisPush();
    }
    else{
      ClearData();
    }
  }
}

void ReadSerial(){
  String myData;
  int lenData;
  
  if (Serial.available() > 0) {
    myData = Serial.readString();
    lenData = myData.length();

    SplitStringUart(myData);
    myData = "";
  }
}

void WriteWifiSerial(){
  String sumDataWifi;

  sumDataWifi = String(StringID) +
          "#" + String(WiFiSSID) + 
          "#" + String(PasswordWifi) +
          "#" + String(statWifi) +
          "#"
          ;

  int length_Data = String(sumDataWifi).length();

  char BufData[length_Data+1];

  sumDataWifi.toCharArray(BufData, length_Data+1);

  delay(300);
  Serial.write(BufData, length_Data+1);
  delay(300);
}

void sendCommand(int commandInt, String ID_TV){
  const byte HEADER = 0x69;
  const byte FIRST_DATA = 0xFF;

  int sumData = FIRST_DATA & (FIRST_DATA - (HEADER + commandInt));

  byte dataSend[3] = {HEADER, commandInt, sumData};
  byte dataSendOn[4] = {0x77, 0x61, 0x6B, 0x65};
  
  if(ID_TV == StringID){
    if(commandInt == 118){
      Serial.write(dataSendOn, 4);
      delay(50);
      Serial.write(dataSend, 3);
    }
    else{
      Serial.write(dataSend, 3);
      delay(50);
    }
  }
}
