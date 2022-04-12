//mqtt data send



WiFiClient espClient;
PubSubClient client(espClient);


//=======================================================================
//  SendDataMQTT: send MQTT data to broker with 'retain' flag set to TRUE
//=======================================================================
void SendDataMQTT (struct sensorData *environment)
{
  char bufferTempF[5];
  char bufferTempC[5];
  char bufferRain[10];
  char bufferRain24[10];


  int hourPtr = timeinfo.tm_hour;
  client.setServer(mqttServer, mqttPort);
  //client.setCallback(callback);

  while (!client.connected()) {
    MonPrintf("Connecting to MQTT...");

    if (client.connect("ESP32Client", mqttUser, mqttPassword))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(1000);
    }
  }
  MQTTPublishInt("boot/", (int)bootCount, true);
  MQTTPublishLong("rssi/", rssi, true);
  MQTTPublishInt("temperatureF/", (int)environment->temperatureF, true);
  MQTTPublishInt("temperatureC/", (int)environment->temperatureC, true);
  MQTTPublishFloat("windSpeed/", environment->windSpeed, true);
  MQTTPublishInt("windDirection/", (int)environment->windDirection, true);
  MQTTPublishString("windCardinalDirection/", environment->windCardinalDirection, true);
  MQTTPublishInt("photoresistor/", (int)environment->photoresistor, true);
#ifndef METRIC
  MQTTPublishFloat("rainfallInterval/", rainfall.intervalRainfall * 0.011, true);
  MQTTPublishFloat("rainfall/", rainfall.hourlyRainfall[hourPtr] * 0.011, true);
  MQTTPublishFloat("rainfall24/", last24() * 0.011, true);
#else
  MQTTPublishFloat("rainfallInterval/", rainfall.intervalRainfall * 0.011 * 25.4, true);
  MQTTPublishFloat("rainfall/", rainfall.hourlyRainfall[hourPtr] * 0.011 * 25.4, true);
  MQTTPublishFloat("rainfall24/", last24() * 0.011 * 25.4, true);
#endif

  MQTTPublishFloat("batteryVoltage/", environment->batteryVoltage, true);
  MQTTPublishFloat("lux/", environment->lux, true);
  MQTTPublishFloat("UVIndex/", environment->UVIndex, true);
  MQTTPublishFloat("relHum/", environment->humidity, true);
  MQTTPublishFloat("pressure/", environment->barometricPressure, true);
  MQTTPublishFloat("caseTemperature/", environment->BMEtemperature, true);
  MQTTPublishInt("batteryADC/", (int)environment->batteryADC, true);
  MQTTPublishInt("ESPcoreF/", (int)environment->coreF, true);
  MQTTPublishInt("ESPcoreC/", (int)environment->coreC, true);
  MQTTPublishInt("timeEnabled/", (int)elapsedTime, true);
  MQTTPublishBool("lowBattery/", lowBattery, true);
  MonPrintf("Issuing mqtt disconnect\n");
  client.disconnect();
  MonPrintf("Disconnected\n");
}

//=======================================================================
//  MQTTPublishString: routine to publish string
//=======================================================================
void MQTTPublishString(const char topic[], char *value, bool retain)
{
  char topicBuffer[256];
  char payload[256];
  int retryCount = 0;
  int status = 0;

  strcpy(topicBuffer, mainTopic);
  strcat(topicBuffer, topic);
  if (!client.connected()) reconnect();
  client.loop();
  sprintf(payload, "%s", value);
#ifdef ExtendedMQTT
  MonPrintf("%s: %s\n", topicBuffer, payload);
#endif
  while (!status && retryCount < 5)
  {
    status = client.publish(topicBuffer, payload, retain);
#ifdef ExtendedMQTT
    MonPrintf("MQTT status: %i\n", status);
#endif
    delay(50);
    retryCount++;
  }
}

//=======================================================================
//  MQTTPublishInt: routine to publish int values as strings
//=======================================================================
void MQTTPublishInt(const char topic[], int value, bool retain)
{
  char topicBuffer[256];
  char payload[256];
  int retryCount = 0;
  int status = 0;

  strcpy(topicBuffer, mainTopic);
  strcat(topicBuffer, topic);
  if (!client.connected()) reconnect();
  client.loop();
  sprintf(payload, "%i", value);
#ifdef ExtendedMQTT
  MonPrintf("%s: %s\n", topicBuffer, payload);
#endif
  while (!status && retryCount < 5)
  {
    status = client.publish(topicBuffer, payload, retain);
#ifdef ExtendedMQTT
    MonPrintf("MQTT status: %i\n", status);
#endif
    delay(50);
    retryCount++;
  }
}


//=======================================================================
//  MQTTPublishLong: routine to publish int values as strings
//=======================================================================
void MQTTPublishLong(const char topic[], long value, bool retain)
{
  char topicBuffer[256];
  char payload[256];
  int retryCount = 0;
  int status = 0;

  strcpy(topicBuffer, mainTopic);
  strcat(topicBuffer, topic);
  if (!client.connected()) reconnect();
  client.loop();
  sprintf(payload, "%li", value);
#ifdef ExtendedMQTT
  MonPrintf("%s: %s\n", topicBuffer, payload);
#endif
  while (!status && retryCount < 5)
  {
    status = client.publish(topicBuffer, payload, retain);
#ifdef ExtendedMQTT
    MonPrintf("MQTT status: %i\n", status);
#endif

    delay(50);
    retryCount++;
  }
}

//=======================================================================
//  MQTTPublishFloat: routine to publish float values as strings
//=======================================================================
void MQTTPublishFloat(const char topic[], float value, bool retain)
{
  char topicBuffer[256];
  char payload[256];
  int retryCount = 0;
  int status = 0;

  strcpy(topicBuffer, mainTopic);
  strcat(topicBuffer, topic);
  if (!client.connected()) reconnect();
  client.loop();
  sprintf(payload, "%6.3f", value);
#ifdef ExtendedMQTT
  MonPrintf("%s: %s\n", topicBuffer, payload);
#endif
  while (!status && retryCount < 5)
  {
    status = client.publish(topicBuffer, payload, retain);
#ifdef ExtendedMQTT
    MonPrintf("MQTT status: %i\n", status);
#endif
    delay(50);
    retryCount++;
  }
}

//=======================================================================
//  MQTTPublishBool: routine to publish bool values as strings
//=======================================================================
void MQTTPublishBool(const char topic[], bool value, bool retain)
{
  char topicBuffer[256];
  char payload[256];
  int retryCount = 0;
  int status = 0;

  strcpy(topicBuffer, mainTopic);
  strcat(topicBuffer, topic);
  if (!client.connected()) reconnect();
  client.loop();
  if (value)
  {
    sprintf(payload, "true");
  }
  else
  {
    sprintf(payload, "false");
  }
#ifdef ExtendedMQTT
  MonPrintf("%s: %s\n", topicBuffer, payload);
#endif
  while (!status && retryCount < 5)
  {
    status = client.publish(topicBuffer, payload, retain);
#ifdef ExtendedMQTT
    MonPrintf("MQTT status: %i\n", status);
#endif
    delay(50);
    retryCount++;
  }
}
//=======================================================================
//  reconnect: MQTT reconnect
//=======================================================================
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
