#ifndef SENSORES_H
#define SENSORES_H

#include <DallasTemperature.h>
#include <DFRobot_ESP_EC.h>

#define EC_PIN A0
#define PH_PIN 35
#define ONE_WIRE_BUS 14

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DFRobot_ESP_EC ec;

float ecValue, tds, temperature = 25, ph;

void iniciarSensores()
{
    sensors.begin();
    ec.begin();
}

void leerSensores()
{
    // Temperatura
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);

    // Solidos disueltos totales (TDS) y conductividad eléctrica (EC)
    float rawEC = analogRead(EC_PIN) / 10.0;
    ecValue = ec.readEC(rawEC, temperature);
    tds = ((ecValue * 1000) / 2);

    // pH
    int rawPH = analogRead(PH_PIN);
    float voltage = rawPH * (3.3 / 4095.0);
    ph = 7 + ((2.5 - voltage) / 0.18);

    ec.calibration(rawEC, temperature);
}

void imprimirDatos()
{
    Serial.printf("Temp: %.2f °C | EC: %.2f mS/cm | TDS: %.2f ppm | pH: %.2f\n", temperature, ecValue, tds, ph);
}

#endif
                                                                                                                                                                                                                                                   