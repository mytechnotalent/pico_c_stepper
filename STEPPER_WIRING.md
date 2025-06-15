# ULN2003 28BYJ-48 Stepper Motor Wiring Guide

## Overview
This project controls 4 ULN2003 28BYJ-48 stepper motors with a Raspberry Pi Pico while avoiding UART pins.

## GPIO Pin Assignments

### Stepper Motor 1
- **IN1**: GPIO 2
- **IN2**: GPIO 3  
- **IN3**: GPIO 6
- **IN4**: GPIO 7
- **VCC**: 5V (VBUS)
- **GND**: GND

### Stepper Motor 2
- **IN1**: GPIO 10
- **IN2**: GPIO 11
- **IN3**: GPIO 14
- **IN4**: GPIO 15
- **VCC**: 5V (VBUS)
- **GND**: GND

### Stepper Motor 3
- **IN1**: GPIO 18
- **IN2**: GPIO 19
- **IN3**: GPIO 20
- **IN4**: GPIO 21
- **VCC**: 5V (VBUS)
- **GND**: GND

### Stepper Motor 4
- **IN1**: GPIO 22
- **IN2**: GPIO 26
- **IN3**: GPIO 27
- **IN4**: GPIO 28
- **VCC**: 5V (VBUS)
- **GND**: GND

### Onboard LED
- **LED**: GPIO 25 (built-in)

## UART Pins Avoided
The following GPIO pins are avoided to prevent interference with UART communication:
- GPIO 0, 1 (UART0)
- GPIO 4, 5 (UART1) 
- GPIO 8, 9 (UART1)
- GPIO 12, 13 (UART0)
- GPIO 16, 17 (UART0)

## Power Supply Notes
- The ULN2003 driver boards require 5V power supply
- Connect 5V from Raspberry Pi Pico VBUS pin (pin 40)
- Ensure adequate power supply (USB power or external 5V supply)
- Each stepper motor draws approximately 160mA

## Operation
The program will:
1. Blink the onboard LED continuously (1 second cycle)
2. Every 5 LED blink cycles, run the stepper motor sequence
3. Each stepper motor rotates 45° clockwise, then 45° counter-clockwise
4. Serial output shows LED status and stepper motor operations

## Connection Diagram
```
Raspberry Pi Pico          ULN2003 Driver Board #1
GPIO 2        -----------> IN1
GPIO 3        -----------> IN2  
GPIO 6        -----------> IN3
GPIO 7        -----------> IN4
VBUS (5V)     -----------> VCC
GND           -----------> GND

(Repeat similar connections for motors 2, 3, and 4 with their respective GPIO pins)
```

## Files Added/Modified
- `src/stepper.h` - Stepper motor driver header
- `src/stepper.c` - Stepper motor driver implementation  
- `src/run.c` - Modified to include stepper control
- `src/run.h` - Updated with stepper function declarations
- `CMakeLists.txt` - Updated to compile stepper.c
