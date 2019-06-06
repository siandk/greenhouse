
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "stdio_setup.h"
#include "GreenhouseInit.h"
#include "WindowOpen.h"
#include "SunDetect.h"
#include "TempDetect.h"
#include "WateringSystem.h"
#include "WaterDetect.h"
#include "MatrixKeyboard.h"
#include "ManualControl.h"
#include "MoistureDetect.h"
#include "lcd.h"

void runCommand(key);
void printStatus(float temp, int lightLevel, int moistureLevel);
void manualControl(char command);

// Global variables used across timers
char mode = 'a';  // 'a': Automatic mode. Components are controlled by sensors. 'm': Manual mode, components are controlled by keyboard
int activeColumn; // Keypad column
int activeRow; // Keypad row
int WS_flag = 0; // Flag for starting the wateringsystem

int main(void)
{
	GreenhouseInit();
	
	while(1) {
		_delay_ms(1);
		// Software delays are used for running the stepmotor.
		// To avoid holding up a interrupt timer while the wateringsystem is running,
		// it is started in main() by using the global WS_flag
		if (WS_flag == 1)
		{
			start(); // Start the wateringsystem
			WS_flag = 0;
		}
	}
}

/**
Interrupt timer for sensor reading, component control, and LCD output.
The watchdog timer is also reset here.
*/
ISR(TIMER1_COMPA_vect)
{
	PORTE |= (1<<PE1);
	if (mode == 'a')
	{
		openWindow(readTempCelsius());
		lightToggle(readLight());
		WS_flag = moistureOK(readMoisture());
	}
	printStatus(readTempCelsius(), readLight(), readMoisture());
	PORTE &= ~(1<<PE1);
	wdt_reset();
}

/**
Interrupt for reading the column of the keypad
*/
ISR(TIMER4_COMPA_vect)
{
	activeColumn = columnScan();
}
/**
Interrupt for reading the row of the keypad
*/
ISR(TIMER4_COMPB_vect)
{
	activeRow = readRow();
	char keyPress = keyDecode(activeColumn, activeRow); // keyDecode returns 0x00 if no key is pressed
	if (keyPress)
	{
		runCommand(keyPress);
	}
}

/**
Interpret the pressed key
*/
void runCommand(char key)
{
	if(mode == 'a' && key == 'A')
	{
		printf("Switching to manual mode\n\r");
		mode = 'm';
	}
	else if(mode == 'm' && key == 'A')
	{
		printf("Switching to automatic mode\n\r");
		mode = 'a';
	}
	else if(mode == 'm')
	{
		manualControl(key);
	}
}
/**
Print the sensor readings to the LCD display
Also displays the current mode of operation
*/
void printStatus(float temp, int lightLevel, int moistureLevel)
{
	char line0[16];
	char line1[16];
	if (waterOK() == 1)
	{
		sprintf(line0, "T   L   M   W  %c", mode);
		sprintf(line1, "%0.0fC %d %d OK!", temp, lightLevel, moistureLevel);
	}
	else
	{
		sprintf(line0, "T   L   M   W  %c", mode);
		sprintf(line1, "%0.0fC %d %d LOW!", temp, lightLevel, moistureLevel);
	}
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts(line0);
	lcd_gotoxy(0,1);
	lcd_puts(line1);
}

/**
Controls components based on keypress
*/
void manualControl(char command)
{
	switch (command)
	{
		case '1':
		lightSwitch();
		break;
		
		case '2':
		windowToggle();
		break;
		
		case '3':
		if(WS_flag == 1)
		{
			printf("Watering already running\n\r");
			break;
		}
		else
		{
			printf("Starting watering system\n\r");
			WS_flag = 1;
			break;
		}
		case 'C':
			rotateClockwise();
		break;
		case 'D':
			rotateCounterClockwise();
		break;
		case '#':
		waterToggle();
		break;
		default:
		break;
	}
}