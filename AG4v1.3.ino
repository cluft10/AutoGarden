#include <DHT.h>  // Including library for dht
#include <ESP8266WiFi.h>
 
String apiKey = "*************";  //Write API key from ThingSpeak

const char *ssid =  "**************";  // WiFi SSID
const char *pass =  "**************";         // WiFi WPA2 Passkey
const char* server = "api.thingspeak.com";

#define DHTPIN D4          //pin where the dht11 is connected
#define SEN13637PIN  A0

DHT dht(DHTPIN, DHT11);

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();

       //Serial.clear(); //Clear the Serial Monitor
       Serial.println();
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.println("Connecting to ");
            Serial.println(ssid);
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
      //Collect Humidity and Temperature from DHT11
      float h = dht.readHumidity();
      float temp = dht.readTemperature();
      float t = ((temp * 9) / 5 )+ 32; // convert C to F
      //Collect Soil Moisture from SEN13637
      int mraw = analogRead(SEN13637PIN);
      int m = map(mraw, 0, 1023, 0, 100);
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                             //Send data to Thingspeak
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(m);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Fahrenheit, Humidity: ");
                             Serial.print(h);
                             Serial.print("%, Soil Moisture Level: ");
                             Serial.print(m);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  //Sample Delay Time in Milliseconds
  delay(300000);
}
