# Cima attiny85

A basic program for attiny 85 to demonstrate Aurduino-less development for this tiny board with processor.

# About ATTINY85

[SoC Atmel 1705 TINY85 20SU](https://www.microchip.com/en-us/product/ATTINY85) is: 
- [AVR based](https://en.wikipedia.org/wiki/AVR_microcontrollers) 8-bit microprocessor 
- 8KB of flash memory 
- 512 B SRAM
- 6 GPIO (HW PWM, AD converter)
- [Complete TINY85 datasheet](https://ww1.microchip.com/downloads/en/devicedoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet-summary.pdf)

[Digispark Breakout board](http://digistump.com/wiki/digispark) is:
- Opensource PCB layout
- With micro USB
- 5V stabilization
- 6 Breakout GPIO pins
- 3 power in/out pins

# Development

## Prereqisities

1. USB-COM drivers: [Digistump.Drivers.zip](https://github.com/digistump/DigistumpArduino/releases/download/1.6.7/Digistump.Drivers.zip)
    - >NOTE: Find the latest release at https://github.com/digistump/DigistumpArduino/releases/
    - Unzip anywhere
    - Install using _Install Drivers.exe_
    - Plug in your ATTINNY 85 board
    - ![Device in device manager](doc/img/intro-lib-usb.png)