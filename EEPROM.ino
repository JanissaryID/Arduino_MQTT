void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
  EEPROM.commit();
}

String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  return String(data);
}

//void writeIntToEEPROM(int addrOffset, const int dataInt)
//{
//  EEPROM.write(addrOffset, dataInt);
//  EEPROM.commit();
//}
//
//int readIntFromEEPROM(int addrOffset)
//{
//  int newStrLen = EEPROM.read(addrOffset);
//  int dataEEPROM = 0;
//  dataEEPROM = EEPROM.read(addrOffset);
//  return dataEEPROM;
//}

void CheckID(){
  EEPROM.begin(255);
  StringID = readStringFromEEPROM(0);
  WiFiSSID = readStringFromEEPROM(40);
  PasswordWifi = readStringFromEEPROM(70);
  
  if(StringID.length() < 15){
    String id = RandID();
    writeStringToEEPROM(0, id);
  }
  
  StringID = readStringFromEEPROM(0);
  WiFiSSID = readStringFromEEPROM(40);
  PasswordWifi = readStringFromEEPROM(70);

  char Buf1[WiFiSSID.length() + 1];
  char Buf2[PasswordWifi.length() + 1];
  
  WiFiSSID.toCharArray(Buf1, WiFiSSID.length() + 1);
  PasswordWifi.toCharArray(Buf2, PasswordWifi.length() + 1);

#if debug
  Serial.println("\nID TV 2 = " + StringID);
  Serial.println(StringID.length());
  Serial.println("SSID 2 = " + String(WiFiSSID));
  Serial.println("PASSWORD 2 = " + String(PasswordWifi));
#endif
    
  
}
