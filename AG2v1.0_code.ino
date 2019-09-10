/*
  AUTOGARDEN
  by Collin T. Luft 
  AG2 CODE V1.0
  created 26 June 2019
  last updated 1 September 2019

  The AG2 System monitors moisture level in the soil of a potted plant and subsequently autonomously delivers water to the plant.
    
*/

#include <Wire.h> 
#include <dht.h>
#include <LiquidCrystal_I2C.h>

dht DHT;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//two soil moisture sensors are utilized
#define moisture1  A0
#define moisture2  A1
#define MAXmoisture 1023
#define DHT11_PIN 13

void setup() {
  // initialize water pump as an output
       pinMode(3,OUTPUT);

  // initialize the lcd 
  lcd.init();
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("AUTOGARDEN");

  for(int i=6; i<10; i++){  // each led is in series with 330 ohms resitor
       pinMode(i,OUTPUT);
       //Each sensor has both a red and green LED assigned to it
       //Sensor 1: Digital 6,7
       //Sensor 2: Digital 8,9
   }
}

void loop()
{
 int chk = DHT.read11(DHT11_PIN);
 if(DHT.temperature > 0){ 
    lcd.setCursor(0,0);
    lcd.print("  AG1 v3.0.1    ");
    lcd.setCursor(0,1);
    lcd.print(" by AutoGarden  ");
    delay(2000);
    
    lcd.setCursor(0,0);
    lcd.print("    Cucumber    ");
    lcd.setCursor(0,1);
    lcd.print("Moisture: ");
    int moist = analogRead(A0);
    int moistpercentile = map(moist, 0, MAXmoisture, 100, 0);
    lcd.print(moistpercentile);
    lcd.print("%          ");
    sens1(moistpercentile);
    delay(2000);
    
    lcd.setCursor(0,0);
    lcd.print("   Bell Pepper   ");
    lcd.setCursor(0,1);
    lcd.print("Moisture: ");
    moist = analogRead(A1);
    moistpercentile = map(moist, 0, MAXmoisture, 100, 0);
    lcd.print(moistpercentile);
    lcd.print("%          ");
    sens2(moistpercentile);
    delay(2000);
    
    lcd.setCursor(0,0);
    lcd.print("Curr. Conditions");
    lcd.setCursor(0,1);
    lcd.print(" Temp: ");
    int tempf = ((DHT.temperature * 9)/5)+32;
    lcd.print(tempf);
    lcd.setCursor(9,1);
    lcd.print((char)223);
    lcd.print("F        ");
    delay(2000);
    
    lcd.setCursor(0,0);
    lcd.print("Curr. Conditions");
    lcd.setCursor(0,1);
    lcd.print(" Temp: ");
    chk = DHT.read11(DHT11_PIN);
    lcd.print(DHT.temperature);
    lcd.setCursor(9,1);
    lcd.print((char)223);
    lcd.print("C        ");
    delay(2000);
    
    lcd.setCursor(0,0);
    lcd.print("Curr. Conditions");
    lcd.setCursor(0,1);
    lcd.print(" Humid: ");
    lcd.print(DHT.humidity);
    lcd.setCursor(10,1);
    lcd.print("%        ");
    delay(2000);
 }
}

void sens1(int percentile){
   if (percentile > 60){
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
   }
   else{
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
   }
}

void sens2(int percentile){
   if (percentile > 60){
      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
   }
   else{
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
   }
}

void water() {
  digitalWrite(3,LOW);
  delay(2000);
  digitalWrite(3,HIGH);
  delay(2000);
}
