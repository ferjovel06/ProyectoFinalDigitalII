#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <WiFi.h>

//const char *ssid = "CLARO1_81FBD4";
//const char *pass = "861W0YNFTY";

//const char *ssid = "CLARO1_378ED8";
//const char *pass = "5HZTSSX42M";

const char *ssid = "Redmi Note 12S";
const char *pass = "123456789";

void conectarWiFi()
{
    Serial.println("Conectando a WiFi...");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado");
}

#endif
