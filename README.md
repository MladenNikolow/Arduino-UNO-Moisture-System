# Arduino-UNO-Moisture-System

<h2>Simple moisture sensor sytem</h2>

<b>Brief:</b>

The system is switched on/off by pressing a button. The [soil moisture sensor](https://erelement.com/sensors/moisture-sensor) starts to measure and the values are displayed on the screen (in percentages). The microcontroller use 2 LEDs to indicate the moisture level. The project is developed in C by direct programming of the chip ([Atmega 328 full documentation](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf). The only libraries used are for the screen:
 - [Wire.h](https://www.arduino.cc/en/reference/wire)
 - [LiquidCrystal_I2C.h](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)
 
<b>Technical Details:</b>

  - using 16 bit's Timer 1 for button deboucing (presacller 8, Overflow - 32 ms)
  - using 8 bit's Timer 2 for the frequency of the measurement (prescaller 1024, Overflow: 0.016256s)
  - using TWI (Two Wired Interface) for the communication with the sensor
  - using ADC (Analog-to-digital-comparator) for the soil moisture sensor
