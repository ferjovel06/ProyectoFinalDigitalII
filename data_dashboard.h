#ifndef DATA_DASHBOARD_H
#define DATA_DASHBOARD_H

void enviarDatosDjango(float temperatura, float ph, float tds)
{
    if (client.connect("192.168.1.95", 8000))
    {
        String postData = "temperatura=" + String(temperatura) +
                          "&ph=" + String(ph) +
                          "&tds=" + String(tds);

        client.print("POST /sensors/datos/ HTTP/1.1\r\n");
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