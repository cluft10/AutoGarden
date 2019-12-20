# AutoGarden
AutoGarden is a student-led project under the direction of Valparaiso University's chapter of the Institute of Electrical and Electronics Engineers (IEEE).  Our mission is to come up with innovative automated solutions that improve the efficiency of home gardening by implementing self-contained gardening system technology to monitor and cultivate plants. The project has designed, developed, and tested multiple different automated agriculture systems utilizing the Arduino Uno/Nano, Raspberry Pi, and NodeMCU 8266. 

AG1 (v.3.0.1, last updated 6/24/19) - Run using an Arduino Uno, the AG1 monitors the soil moisture using the Sparkfun SEN13637 and temperature and humidity using the DHT11. This is in preparation of the AG2 which will integrate self-watering technology with the monitoring system. Capable of monitoring up to two plants at once and indicating a need to water if soil drops below 60% moisture. Red/Green LEDs are used to indicate if watering is needed and an LED display is used to display monitored data.
The AG1 System monitors the following:
    -Temperature - DHT11
    -Humidity - DHT11
    -Soil Moisture - SEN13637
    
AG2 (v.1.1, last updated 12/19/19) - Also known as ArduinH2O, the AG2 utilizes a Arduino Nano to control a +5V DC water pump and standard airline tubing to self-water a given plant when the moisture level in the soil drops below 80%.
The AG2 System monitors the following:
    -Temperature - DHT11/BMP180
    -Humidity - DHT11
    -Barometric Pressure - BMP180
    -Light Intensity - GY-30/BH1750
    -Soil Moisture - SEN13637

AG3 - We are in the process of developing an aeroponics (fogponics) system utilizing a Raspberry Pi microprocessor. We plan to create a self-contained 3D printed housing. Based on a user-indicated location point, weather data will be implemented to adjust light intensity, temperature, and humidity in realtime. Once complete, location specific herbs and vegetables can be grown anywhere using our AutoPonics system.

AG4 (v.1.3, last updated 11/25/19) - A NodeMCU esp8266 collects Temperature, Humidity, and Soil Moisture Data and uploads to a thingspeak API at https://thingspeak.com/channels/898321.
The AG4 System monitors the following:
    -Temperature - DHT11
    -Humidity - DHT11
    -Soil Moisture - SEN13637
