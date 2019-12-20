#include <Wire.h> 

int i = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(4,OUTPUT);
Serial.begin(9600);
Serial.println();
Serial.println("SETUP:");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4, HIGH);
  Serial.println("HIGH");
  delay(2000);
  digitalWrite(4, LOW);
  Serial.println("LOW");
  delay(2000);
}
