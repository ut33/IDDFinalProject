# IDDFinalProject: Environmentally Efficient Smart Home Air Quality Network
*A lab report by Vini Tripathii*

[How Safe is the Air You Breathe -- Why an indoor air filtration system is needed](//https://github.com/ut33/IDDFinalProject/blob/master/Prototype%20Diagram%20UX.pdf) <br/>
<br/>
[Prototype Design](//https://github.com/ut33/IDDFinalProject/blob/master/Prototype%20Diagram%20UX.pdf)
## Product Documentation
Sensor Hub: <picture> ![Photo](RendersV2/Ren1.JPG)
Fan:
Filter System: <filters inside fan> <br/>
Video of complete system in action: https://drive.google.com/file/d/1fjfDov-qPdvtKRKVDF_7Mbi5ONEb0vfH/view?usp=sharing<br/>
Video of sensor readings on phone: <br/>
Video of fan responding to single sensor:<br/>
Video of radios transmitting:<br/>

## Radios
I used NRF24L01 radio modules to wirelessly communicate between the sensor hub and filtration system. For the Metro Mini or Arduino Uno, connect VCC to 3.3V, GND to GND, MOSI (Master Out Slave In) to 11, MISO (Master In Slave Out) to 12 and SCK (Serial Clock) to 13. Other version of Arduino may require different connections. CE (Chip Enable) and CSN (Chip Select Not) can be selected to any digital I/O pin.
Problems with radio: I experienced some inexplicable trouble when using the radio modules when they would randomly start and stop working. The most confusing thing was that the transmitter would not worked if it matched the reciever (which goes against documentation). I managed to get it working by setting the reciever CE = 9 and CSN = 8 and on the transmitter CE = 7 and CSN = 8.<br/>

## Sensors
For this project I used [two](https://wiki.dfrobot.com/Gravity__Analog_Infrared_CO2_Sensor_For_Arduino_SKU__SEN0219) [CO2](https://wiki.dfrobot.com/CO2_Sensor_SKU_SEN0159) sensors, a [gas sensor](http://wiki.seeedstudio.com/Grove-Gas_Sensor-MQ2/), and a [dust sensor](http://wiki.seeedstudio.com/Grove-Dust_Sensor/). The gas sensor can be used to detect a variety of substances such CO, propane and smoke among other by adjusting the weight. Calibrating the sensors took several days.
The average of the sensors readings over last 30 seconds is taken and converted to ppm. This value is then compared to the advisable threshold -- if any sensor's readings are over the threshold, the fan turns on and remains on until the pollutant concentration decreases to an acceptable level.

## Vent System
How to Install: <photo of installation> <br/>
The system will be installed in the window so that fresh air is brought in. The fan faces inside and acts as a vacuum. Before entering the room it passes through several systems.   
Diagram of model <br/>
Photo of pvc model and 3d printed model <br/>
The pollen filter is used to remove large particles, the HEPA filter for PM2.5 (particles with diameter of 2.5 micrometers or less), and the carbon filter removes VOCs (volatile organic compounds)

## Next Steps:
Next steps include creating an model simulation to determine how the room size affects the fan speed required. This will be used to determine the fan size appropriate for an average room -- for larger rooms, installing several filteration systems may become necessary. Additionally, a secondary ventilation system will be added to remove stale air in conjunction with the current system that brings in fresh air. For ease of use, a self-calibrating system for the sensors will be devised. Lastly a machine learning model to predict when pollutants are likely to congregate will be devised.
  
  
