# Arduino-UNO-Moisture-System

Simple moisture sensor sytem, using Arduino uno.

Brief:
The system is switched on/off by pressing a button. The [soil moisture sensor](https://erelement.com/sensors/moisture-sensor) starts to measure and the values are displayed on the screen (in percentages). 2 lamps are used to indicate the moisture level. The project was developed in C by direct programming of the chip ([Atmega 328 full documentation](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf). The only libraries used are for the screen:
 - Wire.h
 - <LiquidCrystal_I2C.h>
