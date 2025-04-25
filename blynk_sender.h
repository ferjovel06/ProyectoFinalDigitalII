#ifndef BLYNK_SENDER_H
#define BLYNK_SENDER_H

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2KniSYuXd"
#define BLYNK_TEMPLATE_NAME "Proyecto Digital"
#define BLYNK_AUTH_TOKEN "djxgy0W7utmoMi2JR7dtR2Y3fbWQrBya"

#include <BlynkSimpleEsp32.h>

extern float temperature, tds, ph;

void iniciarBlynk(const char *ssid, const char *pass)
{
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void enviarBlynk()
{
    Blynk.virtualWrite(V1, temperature);
    Blynk.virtualWrite(V0, tds);
    Blynk.virtualWrite(V2, ph);
}

#endif
