#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>

#define MOTOR1 15
#define MOTOR2 21
#define MOTOR3 5

// Variables globales
extern bool motor1Manual;
extern bool motor2Manual;
extern bool motor3Manual;

extern bool motor1On;
extern bool motor2On;
extern bool motor3On;

extern float ph, tds;

// Tiempos de encendido (solo para modo automático)
unsigned long motor1StartTime = 0;
unsigned long motor2StartTime = 0;
unsigned long motor3StartTime = 0;

const unsigned long AUTO_TIMEOUT = 3000; // 3 segundos

void configurarMotores()
{
    pinMode(MOTOR1, OUTPUT);
    pinMode(MOTOR2, OUTPUT);
    pinMode(MOTOR3, OUTPUT);
    digitalWrite(MOTOR1, LOW);
    digitalWrite(MOTOR2, LOW);
    digitalWrite(MOTOR3, LOW);
}

void controlarMotor() {
    unsigned long now = millis();

    // MOTOR1
    if (!motor1Manual) {
        if (ph > 7.5 && !motor1On) {
            motor1On = true;
            motor1StartTime = now;
        }
        if (motor1On && (now - motor1StartTime >= AUTO_TIMEOUT)) {
            motor1On = false;
        }
    }

    // MOTOR2
    if (!motor2Manual) {
        if (ph < 6.5 && !motor2On) {
            motor2On = true;
            motor2StartTime = now;
        }
        if (motor2On && (now - motor2StartTime >= AUTO_TIMEOUT)) {
            motor2On = false;
        }
    }

    // MOTOR3
    if (!motor3Manual) {
        if (tds > 300.0 && !motor3On) {
            motor3On = true;
            motor3StartTime = now;
        }
        if (motor3On && (now - motor3StartTime >= AUTO_TIMEOUT)) {
            motor3On = false;
        }
    }

    // Aplicar estados a los pines
    digitalWrite(MOTOR1, motor1On ? HIGH : LOW);
    digitalWrite(MOTOR2, motor2On ? HIGH : LOW);
    digitalWrite(MOTOR3, motor3On ? HIGH : LOW);

    // Debug
    Serial.print("Motores encendidos: ");
    if (motor1On) Serial.print("MOTOR1 ");
    if (motor2On) Serial.print("MOTOR2 ");
    if (motor3On) Serial.print("MOTOR3 ");
    if (!motor1On && !motor2On && !motor3On) Serial.print("Ninguno");
    Serial.println();
}

#endif
