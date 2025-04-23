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
 
#define ONE_WIRE_BUS 14               // GPIO14 para sensor de temperatura DS18B20
#define PH_PIN 34                     // Pin analógico para sensor de pH
#define EC_PIN A0                     // Pin analógico para sensor EC (GPIO36)
#define MOTOR1 15
#define MOTOR2 21
#define MOTOR3 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DFRobot_ESP_EC ec;
Adafruit_ADS1115 ads;
 
float ecValue, tds, temperature = 25;
float ph;
 
String apiKey = "LWAG0XTRPKLBCMGH";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "CLARO1_81FBD4";     // replace with your wifi ssid and wpa2 key
const char *pass = "861W0YNFTY";
const char* server = "api.thingspeak.com";
 
WiFiClient client;
 

void conectarWiFi() {
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
}


void leerSensores() {
  // Temperatura
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  // Lectura EC y TDS
  float rawEC = analogRead(EC_PIN)/10.0;
  ecValue = ec.readEC(rawEC, temperature); // convert voltage to EC with temperature compensation
  tds = ((ecValue * 1000) / 2);

  // Lectura pH
  int rawPH = analogRead(PH_PIN);
  float voltage=rawPH*(3.3/4095.0);
  ph=(3.3*voltage);

  ec.calibration(rawEC, temperature); // calibration process by Serail CMD
}


void controlarMotor() {
  // Motor 1 por pH alto
  if (ph > 7.5) {
    digitalWrite(MOTOR1, HIGH);
    Serial.println("Motor 1 encendido por pH alto");
  } else if (ph < 7.5) {
    digitalWrite(MOTOR1, LOW);
  }

  // Motor 2 por pH bajo
  if (ph < 6.5) {
    digitalWrite(MOTOR2, HIGH);
    Serial.println("Motor 2 encendido por pH bajo");
  } else if (ph > 6.5) {
    digitalWrite(MOTOR2, LOW);
  }

  // Motor 3 por TDS alto
  if (tds > 300.0) {
    digitalWrite(MOTOR3, HIGH);
    Serial.println("Motor 3 encendido por TDS alto");
  } else if (tds > 100.0) {
    digitalWrite(MOTOR3, LOW);
  }
}



void imprimirDatos() {
  Serial.printf("Temp: %.2f °C | EC: %.2f mS/cm | TDS: %.2f ppm | pH: %.2f\n", temperature, ecValue, tds, ph);
}


void enviarDatosThingSpeak() {
  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
 
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temperature, 2);
    postStr += "&field2=";
    postStr += String(ecValue, 2);
    postStr += "&field3=";
    postStr += String(ph, 2);
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


void enviarBlynk() {
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V0, tds);
  Blynk.virtualWrite(V2, ph);
}


void setup()
{
  Serial.begin(115200);
  EEPROM.begin(32);
  ec.begin();
  sensors.begin();
  pinMode(PH_PIN,INPUT);
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR3, OUTPUT);
  pinMode(MOTOR3, OUTPUT);
  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, LOW);
  digitalWrite(MOTOR3, LOW);
  conectarWiFi();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
 
 
void loop()
{
  Blynk.run();
  leerSensores();
  controlarMotor();
  imprimirDatos();
  enviarBlynk()
  enviarDatosThingSpeak();
  delay(1500);
}