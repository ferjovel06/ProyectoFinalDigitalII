#ifndef DATA_DASHBOARD_H
#define DATA_DASHBOARD_H

void enviarDatosDjango(float temperatura, float ph, float tds, float ec, bool motor1On, bool motor2On, bool motor3On)
{
    if (client.connect("192.168.1.95", 8000))
    {
        String postData = "temperatura=" + String(temperatura) +
                          "&ph=" + String(ph) +
                          "&tds=" + String(tds) + 
			              "&ec=" + String(ec) +
                          "&motor_ph_alcalino=" + String(motor1On ? "1" : "0") + // Motor 1 encendido o apagado
                          "&motor_ph_acido=" + String(motor2On ? "1" : "0") +    // Motor 2 encendido o apagado
                          "&motor_tds_altos=" + String(motor3On ? "1" : "0");     // Motor 3 encendido o apagado

        client.print("POST /datos/ HTTP/1.1\r\n");
        client.print("Host: 192.168.1.95\r\n");
        client.print("Content-Type: application/x-www-form-urlencoded\r\n");
        client.print("Content-Length: ");
        client.print(postData.length());
        client.print("\r\n\r\n");
        client.print(postData);
        delay(500);
        client.stop();
    }
    else
    {
        Serial.println("No se pudo conectar al servidor Django");
    }
}

#endif
