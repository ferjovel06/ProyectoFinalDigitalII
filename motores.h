#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h> // Para pinMode y digitalWrite

#define MOTOR1 15
#define MOTOR2 21
#define MOTOR3 5

// Definir las variables globales
extern bool motor1Manual;
extern bool motor2Manual;
extern bool motor3Manual;

extern bool motor1On;
extern bool motor2On;
extern bool motor3On;

extern float ph, tds;

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
    if (!motor1Manual)
        motor1On = ph > 7.5;
    if (!motor2Manual)
        motor2On = ph < 6.5;
    if (!motor3Manual)
        motor3On = tds > 300.0;

    digitalWrite(MOTOR1, motor1On ? HIGH : LOW);
    digitalWrite(MOTOR2, motor2On ? HIGH : LOW);
    digitalWrite(MOTOR3, motor3On ? HIGH : LOW);

    Serial.print("Motores encendidos: ");
    if (motor1On)
        Serial.print("MOTOR1 ");
    if (motor2On)
        Serial.print("MOTOR2 ");
    if (motor3On)
        Serial.print("MOTOR3 ");
    if (!motor1On && !motor2On && !motor3On)
        Serial.print("Ninguno");
    Serial.println();
}

#endif
