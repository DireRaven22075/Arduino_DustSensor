#include <SD.h>
#include <SPI.h>
int measurePin = A0;
int ledPower = 7;
int sdPin = 4;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
File file;
void setup(){
  Serial.begin(9600);
  pinMode(ledPower, OUTPUT);
  SD.begin(sdPin);
  file = SD.open("data.csv", FILE_WRITE);
}
void loop(){
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (5.0 / 1024);
  dustDensity = (0.17 * calcVoltage - 0.1)*1000 + 94;
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
  Serial.print(" - Dust Density [ug/m3]: ");
  Serial.println(dustDensity);
  file.write(dustDensity);
  file.write(", ");
  delay(1000);
}
