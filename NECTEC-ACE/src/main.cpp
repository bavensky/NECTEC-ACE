#include <Arduino.h>
#include <HardwareSerial.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <ArduinoJson.h>
#include <MqttConnector.h>
#include <Wire.h>
#include <SPI.h>

#include "init_mqtt.h"
#include "_publish.h"
#include "_receive.h"
#include "_config.h"

#define BUTTON 33
#define rxPin (16)
#define txPin (17)

HardwareSerial mySerial(1);
MqttConnector *mqtt;

int relayPin = 26;
int relayPinState = HIGH;
char myName[40];
int x, y;

unsigned long previousMillis = 0;
const long interval = 500;
unsigned int timeCount = 0;
bool statusCar = false;

void init_hardware()
{
  pinMode(relayPin, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  digitalWrite(relayPin, relayPinState);

  // serial port initialization
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, rxPin, txPin, false);
  delay(10);
  mySerial.print("0\n");
  Serial.println();
  Serial.println("Starting...");
}

void init_wifi()
{
  WiFi.disconnect();
  delay(20);
  WiFi.mode(WIFI_STA);
  delay(50);
  const char *ssid = WIFI_SSID.c_str();
  const char *pass = WIFI_PASSWORD.c_str();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.printf("Connecting to %s:%s\r\n", ssid, pass);
    delay(300);
  }
  Serial.println("WiFi Connected.");
  digitalWrite(2, HIGH);
}

void setup()
{
  init_hardware();
  init_wifi();
  init_mqtt();
}

//   //    sync_advpub("prefix", "topic", "payload", "retain")
//   mqtt->sync_advpub("", "/KIDBRIGHT/gearname/KB001", String(btCount), false);

void loop()
{
  if (digitalRead(BUTTON) == 0)
  {
    delay(200);
    statusCar = true;
  }

  if (statusCar == true)
  {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      timeCount++;
      Serial.print(millis() / 1000);
      Serial.print("  ");
      Serial.println(timeCount);
      mySerial.print(String(map(timeCount, 0, 50, 0, 1000)) + "\n");
    }
    if (timeCount >= 50)
    {
      statusCar = false;
      timeCount = 0;
    }
  }

  mqtt->loop();
} // END LOOP
