#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1X15.h>
#include <DFRobot_ESP_EC.h>
#include <Adafruit_GFX.h>

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2KniSYuXd"
#define BLYNK_TEMPLATE_NAME "Proyecto Digital"
#define BLYNK_AUTH_TOKEN "djxgy0W7utmoMi2JR7dtR2Y3fbWQrBya"

#include <BlynkSimpleEsp32.h>
 
#define ONE_WIRE_BUS 14                // this is the gpio pin 13 on esp32.
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
 
DFRobot_ESP_EC ec;
Adafruit_ADS1115 ads;
 
float voltage, ecValue, temperature = 25;
 
String apiKey = "LWAG0XTRPKLBCMGH";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "CLARO2_378ED8";     // replace with your wifi ssid and wpa2 key
const char *pass = "5HZTSSX42M";
const char* server = "api.thingspeak.com";
 
WiFiClient client;
 
void setup()
{
  Serial.begin(115200);
  EEPROM.begin(32);//needed EEPROM.begin to store calibration k in eeprom
  ec.begin();
  sensors.begin();

  Serial.println("Connecting to ");
  Serial.println(ssid);
 
 
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
 
 
void loop()
{
  Blynk.run();
  voltage = analogRead(A0); // A0 is the gpio 36
  Serial.print("Voltage:");
  Serial.print(voltage, 2);
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);  // read your temperature sensor to execute temperature compensation
  ecValue = ec.readEC(voltage, temperature); // convert voltage to EC with temperature compensation
 
  Serial.print("Temperature:");
  Serial.print(temperature, 2);
  Serial.println("ºC");
 
  Serial.print("EC:");
  Serial.println(ecValue, 2);

  delay(1500);  // Pausa de 1.5 segundos antes de actualizar la pantalla
 
  ec.calibration(voltage, temperature); // calibration process by Serail CMD

  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V0, ecValue);
 
  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
 
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temperature, 2);
    postStr += "&field2=";
    postStr += String(ecValue, 2);
    postStr += "\r\n\r\n";
    delay(500);
 
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    delay(500);
  }
  client.stop();
}