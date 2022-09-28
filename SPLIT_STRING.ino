void SplitString(String ssidPass){
#if debug
  Serial.println(ssidPass);
#endif
  String myWord = "";
  String SplitWord[3];
  int b = 0;
  
  for(int a = 0; a < ssidPass.length(); a++){
    if(ssidPass[a] != '#'){
      myWord += ssidPass[a];
    }
    else{
      SplitWord[b] = myWord;
      myWord = "";
      b++;
    }
  }
#if debug
  Serial.println();
  Serial.println(SplitWord[1]);
#endif
  writeStringToEEPROM(40, SplitWord[1]);
#if debug
  Serial.println(SplitWord[2]);
#endif
  writeStringToEEPROM(70, SplitWord[2]);
}

void SplitStringUart(String myData){
#if debug
  Serial.println(myData);
#endif
  String myWord = "";
  String SplitWord[11];
  int b = 0;
  
  for(int a = 0; a < myData.length(); a++){
    if(myData[a] != '#'){
      if(myData[a] != 0x00){
        myWord += myData[a];
        // Serial.println(myData[a], HEX);
      }
    }
    else{
      
      SplitWord[b] = myWord;
      myWord = "";
      b++;
    }
  }

  for(int a = 0; a < b; a++){
    ProcessDataSerialTv(SplitWord[a],a);
  }
#if debug
  Serial.println();
#endif
}

void SplitStringSW(String sw){
  String myWord = "";
  String SplitWord[4];
  int b = 0;
  
  for(int a = 0; a < (sw.length()-1); a++){
    if(sw[a] != '"'){
      myWord += sw[a];
    }
    else{
      SplitWord[b] = myWord;
      myWord = "";
      b++;
    }
  }
  dataTvString.swVersion1 = SplitWord[0].substring(1,9);
  dataTvString.swVersion2 = SplitWord[1];
  dataTvString.swVersion3 = SplitWord[2];
}
