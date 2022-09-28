#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

#define debug true

#define LED 2

// WiFi
const char *ssid = "Kuy"; // Enter your WiFi name
const char *password = "inipassword123";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker-dev.iot.polytron.angkasa.id";
const char *topic = "test/monitor";
const char *topic_remote = "/test/remote";
const char *mqtt_username = "krisna_rw";
const char *mqtt_password = "krisna-software";
const int mqtt_port = 9913;

//#define WIFISSID "Biznet.Wifi"
//#define PASSWORD "InetBizn3T"

//#define WIFISSID "Indihome.Wifi"
//#define PASSWORD "MemangCanggih"

String WiFiSSID = "";
String PasswordWifi = "";
String statWifi = "0";

const String NO_COMMAND = "0xFA";
const byte HEADER = 0x69;
const byte FIRST_DATA = 0xFF;

char letters[63] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
                    'k', 'l',  'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                    'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', 
                    '5', '6', '7', '8', '9', '0', 'A', 'B', 'C', 'D', 
                    'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',  'M', 'N', 
                    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
                    'Y', 'Z'};

String StringID = "";
int lengthID = 0;

// variable Data TV bertype Integer
struct myDataTv
{
  uint32_t Freq;
  uint32_t Post;
  uint16_t Time;
  uint16_t Picture;
  uint16_t Sound;
} dataTvStringInt;

// variable Data TV bertype String
struct myDataTvString
{
  String swVersion1;
  String swVersion2;
  String swVersion3;
  String channelTv;
  String projectVersion;
  String macAddressTV;
} dataTvString;

struct myDataWifi
{
  String mySSID;
  String myPassword;
} dataTvWifi;

long previousMillis = 0;
long interval = 10;   

long previousMillisPush = 0;
long intervalPush = 100;   

long previousMillisPushWifi = 0;
long intervalPushWifi = 200;  

long previousMillisConnectBroker = 0;
long intervalConnectBroker = 400; 

// int myFreq, myPost, myPic, mySound, myTime;

String statRestart = "";

DynamicJsonDocument doc(1024);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
//  Serial2.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(LED, LOW);

  CheckID();

  WriteWifiSerial();

  initWiFi();

#if debug
    Serial.print("RRSI: ");
    Serial.println(WiFi.RSSI());
#endif

  if ((WiFi.status() == WL_CONNECTED)) {
    connectMqttBroker();
    // subscribeData();
  }
}

void loop() {
  Milis();
  LedIndicatiorWiFi();
  client.loop();
}