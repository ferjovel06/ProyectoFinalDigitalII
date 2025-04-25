// Configura el pin analógico
const int pHSensorPin = A0;
float calibration_offset = 7.0; // Puedes ajustar este valor tras calibrar

void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(pHSensorPin);
  
  // Conversión a voltaje (en una placa de 5V)
  float voltage = analogValue * (5.0 / 1023.0);
  
  // Conversión aproximada de voltaje a pH
  float pH = 7 + ((2.5 - voltage) / 0.18) + calibration_offset;

  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V | pH: ");
  Serial.println(pH, 2);

  delay(1000); // Espera 1 segundo entre lecturas
}
