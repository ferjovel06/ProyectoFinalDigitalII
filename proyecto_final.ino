#include <EEPROM.h>
#include "wifi_config.h"
#include "sensores.h"
#include "motores.h"
#include "thingspeak_sender.h"
#include "blynk_sender.h"
#include "data_dashboard.h"

void setup() {
  Serial.begin(115200);
  EEPROM.begin(32);
  iniciarSensores();
  configurarMotores();
  conectarWiFi();
  //iniciarBlynk(ssid, pass);
}

void loop() {
  //Blynk.run();
  leerSensores();
  controlarMotor();
  imprimirDatos();
  //enviarBlynk();
  enviarDatosThingSpeak();
  enviarDatosDjango(temperature, ph, tds, ecValue);
  delay(1500);
}
