
# Arduino UNO Moisture Sensor System

## Overview

A simple soil moisture monitoring system using Arduino UNO, a soil moisture sensor, LCD display, and two LEDs for visual indication. The system is programmed in C/C++ with direct register manipulation for learning and performance.

## Features

- Toggle system on/off with a button
- Real-time soil moisture measurement (displayed as percentage)
- Visual feedback using two LEDs (red/green) based on moisture level
- LCD display for user feedback
- Efficient use of hardware timers and interrupts

## Hardware Requirements

- Arduino UNO (ATmega328P)
- Soil moisture sensor ([example](https://erelement.com/sensors/moisture-sensor))
- 16x2 I2C LCD display
- 2 LEDs (red, green)
- 2 resistors (for LEDs)
- Push button
- Jumper wires, breadboard

## Wiring Diagram

> **Note:** Please refer to your sensor and LCD documentation for exact pinouts.

| Component         | Arduino Pin         |
|-------------------|--------------------|
| Soil Sensor (Aout)| A2                 |
| Button            | D2 (INT0)          |
| Green LED         | D8 (PB0)           |
| Red LED           | D9 (PB1)           |
| LCD SDA           | A4                 |
| LCD SCL           | A5                 |


## Software Details

- Uses 16-bit Timer1 for button debouncing (prescaler 8, overflow ~32ms)
- Uses 8-bit Timer2 for measurement frequency (prescaler 1024, overflow ~16ms)
- TWI (I2C) for LCD communication
- ADC for soil moisture sensor
- Minimal use of external libraries: [Wire.h](https://www.arduino.cc/en/reference/wire), [LiquidCrystal_I2C.h](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)

## Getting Started

1. **Clone or Download** this repository.
2. **Connect hardware** as per the wiring diagram above.
3. **Install Arduino IDE** and required libraries:
  - [Wire.h](https://www.arduino.cc/en/reference/wire) (built-in)
  - [LiquidCrystal_I2C.h](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)
4. **Open `main.ino`** in Arduino IDE.
5. **Upload** to your Arduino UNO.

## Usage

- Press the button to turn the system on/off.
- The LCD will display the current soil moisture percentage.
- Green LED: Moisture in optimal range (30% < value < 70%)
- Red LED: Moisture too low or too high (≤30% or ≥70%)

## Project Structure

- `main.ino` - Main source code for the project
- `README.md` - Project documentation

## References

- [ATmega328P Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
- [Wire.h Documentation](https://www.arduino.cc/en/reference/wire)
- [LiquidCrystal_I2C Library](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)

## Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you would like to change.

## License

This project is open source and available under the MIT License.
