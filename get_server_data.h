#ifndef GET_SERVER_DATA_H
#define GET_SERVER_DATA_H

#include <PubSubClient.h> // ¡No olvides incluir esta librería!
#include <Arduino.h>      // Para Serial.print()

extern PubSubClient mqttClient; // Le dices que existe

void mqttCallback(char *topic, byte *message, unsigned int length)
{
    String msg;
    for (int i = 0; i < length; i++)
        msg += (char)message[i];

    Serial.print("Mensaje en topic: ");
    Serial.println(topic);
    Serial.print("Mensaje: ");
    Serial.println(msg);

    if (strcmp(topic, "sistema/motor_ph_alcalino") == 0)
    {
        if (msg == "ON")
        {
            motor1Manual = true;
            Serial.println("Encendiendo motor alcalino...");
            motor1On = true;
            digitalWrite(MOTOR1, HIGH);
        }
        else if (msg == "OFF")
        {
            motor1Manual = true;
            Serial.println("Apagando motor alcalino...");
            motor1On = false;
            digitalWrite(MOTOR1, LOW);
        }
        else if (msg == "AUTO")
        {
            motor1Manual = false;
            Serial.println("Motor alcalino vuelve a automático.");
        }
    }
    else if (strcmp(topic, "sistema/motor_ph_acido") == 0)
    {
        if (msg == "ON")
        {
            motor2Manual = true;
            Serial.println("Encendiendo motor ácido...");
            motor2On = true;
            digitalWrite(MOTOR2, HIGH);
        }
        else if (msg == "OFF")
        {
            motor2Manual = true;
            Serial.println("Apagando motor ácido...");
            motor2On = false;
            digitalWrite(MOTOR2, LOW);
        }
        else if (msg == "AUTO")
        {
            motor2Manual = false;
            Serial.println("Motor ácido vuelve a automático.");
        }
    }
    else if (strcmp(topic, "sistema/motor_tds_altos") == 0)
    {
        if (msg == "ON")
        {
            motor3Manual = true;
            Serial.println("Encendiendo motor TDS altos...");
            motor3On = true;
            digitalWrite(MOTOR3, HIGH);
        }
        else if (msg == "OFF")
        {
            motor3Manual = true;
            Serial.println("Apagando motor TDS altos...");
            motor3On = false;
            digitalWrite(MOTOR3, LOW);
        }
        else if (msg == "AUTO")
        {
            motor3Manual = false;
            Serial.println("Motor TDS altos vuelve a automático.");
        }
    }
    else
    {
        Serial.println("Topic desconocido.");
    }
}

unsigned long lastReconnectAttempt = 0;

bool reconnectMQTT()
{
    if (!mqttClient.connected())
    {
        unsigned long now = millis();
        if (now - lastReconnectAttempt > 5000)
        {
            lastReconnectAttempt = now;
            Serial.print("Intentando conexión MQTT...");
            if (mqttClient.connect("WaterQualityMonitorESP32"))
            {
                Serial.println("Conectado!");
                mqttClient.subscribe("sistema/motor_ph_alcalino");
                mqttClient.subscribe("sistema/motor_ph_acido");
                mqttClient.subscribe("sistema/motor_tds_altos");
                return true;
            }
            else
            {
                Serial.print("Fallo, rc=");
                Serial.print(mqttClient.state());
                Serial.println(" Reintentando pronto...");
            }
        }
        return false;
    }
    return true;
}

#endif // GET_SERVER_DATA_H
