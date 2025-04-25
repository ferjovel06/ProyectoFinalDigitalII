#ifndef THINGSPEAK_SENDER_H
#define THINGSPEAK_SENDER_H

#include <WiFi.h>

WiFiClient client;
const char *server = "api.thingspeak.com";
String apiKey = "LWAG0XTRPKLBCMGH";

extern float temperature, ecValue, ph;

void enviarDatosThingSpeak()
{
    if (client.connect(server, 80))
    {
        String postStr = apiKey;
        postStr += "&field1=" + String(temperature, 2);
        postStr += "&field2=" + String(ecValue, 2);
        postStr += "&field3=" + String(ph, 2);
        postStr += "\r\n\r\n";

        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: " + String(postStr.length()) + "\n\n");
        client.print(postStr);
        delay(500);
    }
    client.stop();
}

#endif
