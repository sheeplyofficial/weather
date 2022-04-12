//=============================================================
//Variables for wifi server setup and api keys for IOT
//Constants for WAKE frequency and UOM for sensors
//=============================================================

//===========================================
//Controls supression of the MonPrintf function to serial
//===========================================
#define SerialMonitor

//===========================================
//WiFi connection
//===========================================
char ssid[] = "AmiNet"; // WiFi Router ssid
char pass[] = "Amadeusz1Ofca"; // WiFi Router password

//===========================================
//Blynk connection
//===========================================
char auth[] = "password";
const char* server = "api.blynk.com";

//===========================================
//Thinkspeak connection
//===========================================
const char* thingspeak_server = "api.thingspeak.com";
const char* api_key = "api_key";

//===========================================
//MQTT broker connection
//===========================================
//const char* mqttServer = "test.mosquitto.org";
const char* mqttServer = "broker.mqttdashboard.com";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
const char mainTopic[20] = "WetSheep/";


//===========================================
//Metric or Imperial measurements
//===========================================
#define METRIC

//===========================================
//Use optional NVM for backup
//This is a failsafe for RESET events out of
//system control
//===========================================
//#define USE_EEPROM

//===========================================
//BH1750 Enable
//===========================================
//#define BH1750Enable

//===========================================
//Anemometer Calibration
//===========================================
//I see 2 switch pulls to GND per revolation. Not sure what others see
#define WIND_TICKS_PER_REVOLUTION 2

//===========================================
//Set how often to wake and read sensors
//===========================================
//const int UpdateIntervalSeconds = 15 * 60;  //Sleep timer (900s) for my normal operation
const int UpdateIntervalSeconds = 1 * 60;  //Sleep timer (60s) testing

//===========================================
//Battery calibration
//===========================================
//batteryCalFactor = measured battery voltage/ADC reading
#define batteryCalFactor .0011804

//===========================================
//Timezone information
//===========================================
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 2 * 3600;
const int   daylightOffset_sec = 0 * 3600;

//========================= Enable Blynk, MQTT or Thingspeak ===================================
//const String App = "BLYNK";         //  alternative is line below
//const String App = "Thingspeak"; //  alternative is line above
const String App = "MQTT";         //  alternative is line below
