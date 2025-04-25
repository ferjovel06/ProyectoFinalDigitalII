#ifndef MOTORES_H
#define MOTORES_H

#define MOTOR1 15
#define MOTOR2 21
#define MOTOR3 5

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

void controlarMotor()
{
    digitalWrite(MOTOR1, ph > 7.5 ? HIGH : LOW);
    digitalWrite(MOTOR2, ph < 6.5 ? HIGH : LOW);
    digitalWrite(MOTOR3, tds > 300.0 ? HIGH : LOW);
}

#endif
