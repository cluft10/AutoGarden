/*
  AUTOGARDEN
  by Collin T. Luft 
  AG2 CODE V1.1.1
  created 17 December 2019
  last updated 20 December 2019

  The AG2 System monitors the following:
    -Temperature - DHT11/BMP180
    -Humidity - DHT11
    -Barometric Pressure - BMP180
    -Light Intensity - GY-30/BH1750
    -Soil Moisture - SEN13637
    
  Additionally, the system delivers water to the plant
  when the soil moisture level drops below 80%
    
*/

#include <Wire.h> 
#include <dht.h>
#include <LiquidCrystal_I2C.h>
#include <SFE_BMP180.h>

dht DHT;
// set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27,20,4);  
SFE_BMP180 bmp180;

int BMP180address = 0x77; //I2C Address of BMP180 Pressure Sensor
int BH1750address = 0x23; //I2C Address of BH1750 Light Sensor
byte buff[2];

#define SMPin  A0 //Analog Pin location of SEN13637 Output
#define DHT11_PIN 7 //Digital Pin location of DHT11 Output
#define PUMP_PIN 4 //Digital Pin location to control +5V pump via 2N2222 Transistor
#define ALTITUDE 241.0 // Altitude of AutoGarden HQ in St. Louis, MO. in meters
#define BMP085_I2CADDR 0x77
#define DELAYTIME 5 // Seconds of Delay between each screen change

void setup() {
  Serial.begin(9600);
  Serial.println("REBOOT");
  lcd.init(); // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("AUTOGARDEN");
  lcd.setCursor(5,2);
  lcd.print("LOADING...");
  bool success = bmp180.begin();
  pinMode(4,OUTPUT); //Pump Control Output
}

void loop() {
 delay(DELAYTIME * 1000);
 lcd.clear();
 screen1(); //Temperature(C), Humidity, Soil Moisture
 delay(DELAYTIME * 1000);
 lcd.clear();
 screen2(); //Temperature(F), Pressure, Light
}

void screen1() {
  int chk = DHT.read11(DHT11_PIN); //Read from DHT11

  //Print Line 1: Heading
  lcd.setCursor(5,0);
  lcd.print("AUTOGARDEN");

  //Print Line 2: Temperature
  lcd.setCursor(0,1);
  lcd.print("TEMPERATURE:");
  float temp = DHT.temperature;
  lcd.setCursor(15,1);
  lcd.print(temp);
  lcd.setCursor(17,1);
  lcd.print((char)223);
  lcd.print("C ");

  //Print Line 3: Humidity
  lcd.setCursor(0,2);
  lcd.print("HUMIDITY:");
  float h = DHT.humidity;
  lcd.setCursor(15,2);
  lcd.print(h);
  lcd.setCursor(17,2);
  lcd.print("%  "); 

  //Print Line 4: Soil Moisture
  lcd.setCursor(0,3);
  lcd.print("SOIL MOISTURE: ");
  int mraw = analogRead(SMPin);
  int m = map(mraw, 0, 1023, 0, 100); 
  lcd.print(m);  
  lcd.setCursor(17,3);
  lcd.print("%"); 

  //Check if watering is needed
  if (m < 80){
  pumpWater();  
  }
}

void screen2() {
  int chk = DHT.read11(DHT11_PIN); //Read from DHT11

  //Print Line 1: Heading
  lcd.setCursor(5,0);
  lcd.print("AG2 v1.1.1");

  //Print Line 2: Temperature
  lcd.setCursor(0,1);
  lcd.print("TEMPERATURE:");
  int tempf = ((DHT.temperature * 9)/5)+32; //Fahrenheit Conversion
  lcd.setCursor(15,1);
  lcd.print(tempf);  
  lcd.setCursor(17,1);
  lcd.print((char)223);
  lcd.print("F "); 

  //Print Line 3: Pressure
  double PressureRead = PressureTest();
  lcd.setCursor(0,2);
  lcd.print("PRESSURE: ");
  lcd.print(PressureRead);
  lcd.setCursor(17,2);
  lcd.print("mb"); 

  //Print Line 4: Light
  uint16_t lightlevel = readLight();
  lcd.setCursor(0,3);
  lcd.print("LIGHT INT:  ");
  if (lightlevel < 10000) {
    lcd.print(" ");
    
    if (lightlevel < 1000) {
      lcd.print(" ");
      
      if (lightlevel < 100) {
      lcd.print(" ");
        
        if (lightlevel < 10) {
        lcd.print(" ");
  }}}}
  lcd.print(lightlevel);
  lcd.setCursor(17,3);
  lcd.print("lx");    
}

uint16_t readLight()
{
  int i;
  uint16_t value=0;
  BH1750_Init(BH1750address);
   
  if(2==BH1750_Read(BH1750address))
  {
    value=((buff[0]<<8)|buff[1])/1.2;
  }
  return value;
}
 
int BH1750_Read(int address) 
{
  int i=0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while(Wire.available()) 
  {
    buff[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();  
  return i;
}
 
void BH1750_Init(int address) 
{
  Wire.beginTransmission(address);
  Wire.write(0x10);
  Wire.endTransmission();
}

void pumpWater(){
  digitalWrite(PUMP_PIN, HIGH);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("AUTOGARDEN");
  lcd.setCursor(2,2);
  lcd.print("DELIVERING WATER");
  delay(10000);
  digitalWrite(PUMP_PIN, LOW);
  lcd.clear();
}

double PressureTest()
{
  char status;
  double T,P,p0,a;
  // You must first get a temperature measurement to perform a pressure reading.
  status = bmp180.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);
    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.
    status = bmp180.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.
      status = bmp180.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);
        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = bmp180.getPressure(P,T);
        if (status != 0)
        {
          // The pressure sensor returns abolute pressure, which varies with altitude.
          // To remove the effects of altitude, use the sealevel function and your current altitude.
          // This number is commonly used in weather reports.
          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
          // Result: p0 = sea-level compensated pressure in mb
          p0 = bmp180.sealevel(P,ALTITUDE); // we're at 210 meters (St. Louis, MO)
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
  return p0;
}
