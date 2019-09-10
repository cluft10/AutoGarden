# AutoGarden
Implementing self-contained gardening system technology to monitor and cultivate plants. The project has designed, developed, and tested multiple different automated agriculture systems utilizing the Arduino Uno/Nano, Raspberry Pi, and NodeMCU 8266. 

ArduinH2O:

AG1 (v.3.0.1, last updated 6/24/19) - Part of the ArduinH2O project, the AG1 monitors the soil moisture using the Sparkfun SEN13637 and temperature and humidity using the DHT11. This is in preparation of the AG2 which will integrate self-watering technology with the monitoring system. Capable of monitoring up to two plants at once and indicating a need to water if soil drops below 60% moisture. Red/Green LEDs are used to indicate if watering is needed and an LED display is used to display monitored data.

AG2 (v.1.0, last updated 9/1/19) - The monitoring system of the AG1 is combined with a +5V DC water pump and standard airline tubing to self-water a given plant when the moisture level in the soil drops below 60%.
