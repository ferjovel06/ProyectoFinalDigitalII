#include <EEPROM.h>
#include <PubSubClient.h>
#include "wifi_config.h"
#include "sensores.h"
#include "motores.h"
#include "data_dashboard.h"
#include "get_server_data.h"

bool motor1Manual = false;
bool motor2Manual = false;
bool motor3Manual = false;

bool motor1On = false;
bool motor2On = false;
bool motor3On = false;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  Serial.begin(115200);
  EEPROM.begin(32);
  iniciarSensores();
  configurarMotores();
  conectarWiFi();
  mqttClient.setServer("192.168.177.32", 1883); 
  mqttClient.setCallback(mqttCallback);          
  reconnectMQTT();   
}

void loop()
{
  if (!mqttClient.connected())
  {
    reconnectMQTT();
  }
  mqttClient.loop();
  leerSensores();
  controlarMotor();
  enviarDatosDjango(temperature, ph, tds, ecValue, motor1On, motor2On, motor3On);
  imprimirDatos();
  delay(1500);
}
