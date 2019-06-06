# Greenhouse Configuration Documentation

## General
All the components have configurable settings in their include files. This means the components can easily be reconfigured to use different ports, timers, etc.

Additionally, all components have an initialization function named in the style of SD_init, WD_init, etc. These functions are standalone, so the components can be used independently of eachother.

The documentation below shows the components configured with their default settings

## Greenhouse
This is the main program. Consisting of a main(), and 2 timers.

The first timer (Timer 1) controls the automatic controls, and the LCD display output

The timer is set up with a 2 second delay, and includes the watchdog timer reset (The watchdog timer has a 4 second timeout)

Delay:

- T=1f=116M=62.5ns
- (Tdelay / (Tcpu * Prescaler)) - 1 = (2s / (62,5nSek * 1024)) - 1 = 31249

The main() functions sole purpose is to start the watering system, if the global WS_flag has been set to 1.

The reason for using main() for the wateringsystem, is due to the software delay, between the steps in the stepmotor pattern.

By using main(), we make sure a timer is not halted, while the wateringsystem is running.

## SunDetect
Photocell and LED control
***

Uses an ADC pin for reading the sensor data, and a port for toggling the LED

|Register|     |     |     |     |
|--------|-----|-----|-----|-----|
|ADMUX   |REFS0|     |     |     |
|DIDR0   |ADC0D|     |     |     |
|ADCSRA  |ADEN |ADPS2|ADPS1|ADPS0|
|DDRA    |PA0  |     |     |     |

ADC pin 0 MUX: **0b00000000**

## WaterDetect
Waterlevel sensor
***
Uses an ADC pin to read the water level


|Register|     |     |     |     |
|--------|-----|-----|-----|-----|
|ADMUX   |REFS0|     |     |     |
|DIDR0   |ADC3D|     |     |     |
|ADCSRA  |ADEN |ADPS2|ADPS1|ADPS0|

ADC pin 3 MUX: **0b00000011**

## MoistureDetect
Ground moisture sensor
***
Uses an ADC pin to read the moisture in the ground.

|Register|     |     |     |     |
|--------|-----|-----|-----|-----|
|ADMUX   |REFS0|     |     |     |
|DIDR0   |ADC2D|     |     |     |
|ADCSRA  |ADEN |ADPS2|ADPS1|ADPS0|

ADC pin 2 MUX: **0b00000010**

## TempDetect
Temperature sensor
***
Uses an ADC pin to read the temperature

|Register|     |     |     |     |
|--------|-----|-----|-----|-----|
|ADMUX   |REFS0|     |     |     |
|DIDR0   |ADC1D|     |     |     |
|ADCSRA  |ADEN |ADPS2|ADPS1|ADPS0|

ADC pin 1 MUX: **0b00000001**

## WindowOpen
Uses a servo motor to automatically or manually open a window
***

|Register|     |     |     |     |
|--------|-----|-----|-----|-----|
|TCCR3A   |COM3B1|   |     |     |
|TCCR3B   |WGM33|CS31|     |     |
|DDRE     |PE4  |    |     |     |

Timer 3 configuration (servo motor):
- Phase and frequency correct mode
- Clear OCR3B on compare match
- Prescaler /8
- Top (ICR3): 20000

Top (50hz)= fclk / (2 * N * hz)  |  16e6 / (2 * 8 * 50) = 20000


## MatrixKeyboard
Keyboard using 4 output ports and 4 input pins
***

The 4 output ports are used for the keyboard columns, and the 4 input pins are used for the rows

|Register|      |      |     |      |
|--------|------|----- |-----|------|
|DDRK    |PK0   |PK1   |PK2  |PK3   |
|PORTK   |0xFE  |      |     |      |
|TCCR4B  |CS41  |CS40  |WGM42|      |
|TIMSK4  |OCIE4A|OCIE4B|     |      |

The timer delay for the Matrix Keyboard has been set using trial and error, to find the best fit, instead of calculating a delay

### Column and row overview

**Port**: K

- Column 4: 0b00001110 PK0
- Column 3: 0b00001101 PK1
- Column 2: 0b00001011 PK2
- Column 1: 0b00000111 PK3

**Pin**: K 4-7


## WateringSystem
Wateringsystem using a stepmotor and a servo motor
***

|Register|      |      |     |      |
|--------|------|----- |-----|------|
|DDRB    |PB0   |PB1   |PB2  |PB3   |
|DDRE    |PE5   |      |     |      |
|TCCR3A  |COM3C1|CS40  |WGM42|      |
|TCCR3B  |WGM33 |CS31  |     |      |

Timer 3 configuration (servo motor):
- Phase and frequency correct mode
- Clear OCR3C on compare match
- Prescaler /8
- Top (ICR3): 20000

Top(50hz) = fclk / (2 * N * hz)  |  16e6 / (2 * 8 * 50) = 20000

### Stepmotor details
The rotateClockwise/counterClockwise function moves the stepmotor 8 steps.

It takes 4096 steps for a full revolution of the stepmotor. This means that for a full revolution, the movement function has to be run 512 times
- 4096 / 8 = 512

***Stepmotor pattern:***

|PB0 |PB1 |PB2 |PB3 |   |
|----|----|----|----|---|
|1   |0   |0   |0   |   |
|1   |1   |0   |0   |   |
|0   |1   |0   |0   |   |
|0   |1   |1   |0   |   |
|0   |0   |1   |0   |   |
|0   |0   |1   |1   |   |
|0   |0   |0   |1   |   |
|1   |0   |0   |1   |   |

## Quick Overview

### ADC
|ADC Pin |Usage      |MUX       |     |      |
|--------|-----------|----------|-----|------|
|Pin 0   |Photocell  |0b00000000|     |      |
|Pin 1   |Temperature|0b00000001|     |      |
|Pin 2   |Moisture   |0b00000010|     |      |
|Pin 3   |Water level|0b00000011|     |      |

### PORTS
|Port    |Usage        |Pxn-Pxn   |In/Out|      |
|--------|-------------|----------|------|------|
|A       |LED toggle   |0         |Out   |      |
|B       |Stepmotor    |0-3       |Out   |      |
|E       |WO Servo(PWM)|4         |Out   |      |
|E       |WS Servo(PWM)|5         |Out   |      |
|J       |Relay        |1         |Out   |      |
|K       |Keyboard Col |0-3       |Out   |      |
|K       |Keyboard Row |4-7       |In    |      |
### TIMERS

|Timer # |Mode|OCRnA                |OCRnA #|OCRnB          |OCRnB #|OCRnC            |OCRnC #|Prescaler|In files                  |
|--------|----|---------------------|-------|---------------|-------|-----------------|-------|---------|--------------------------|
|Timer 1 |0   |Sensor read interrupt|31248‬  |               |       |                 |       |1024     |main                      |
|        |    |                     |       |               |       |                 |       |         |                          |
|Timer 3 |8   |                     |       |WO Servo       |1-2000 |WS Servo         |1-2000 |8        |WateringSystem, WindowOpen|
|Timer 4 |4   |Keypad column scan   |64000  |Keypad row scan|32000  |                 |       |8        |main, MatrixKeyboard      |

### By Component