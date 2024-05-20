#include <OneWire.h>
#include <DallasTemperature.h>

// Pinos do Arduino
const int pinSensorUmidade = A0; 
const int pinRelay = 8; 



void setup() {
  Serial.begin(9600); 
  pinMode(pinRelay, OUTPUT); 
  sensors.begin(); 
}

void loop() {
  int umidade = analogRead(pinSensorUmidade); 
  Serial.print("Umidade: ");
  Serial.println(umidade);

  if (umidade > 750) {
    digitalWrite(pinRelay, HIGH); 
    Serial.println("Acrescentando 100ml");
    delay(3000); 
    digitalWrite(pinRelay, LOW); 
    delay(10000); 
  } else {
    Serial.println("Volto a verificar em 10 minutos");
    delay(600000); 
  }
}
