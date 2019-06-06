/**
 *Title:     Photocell & LED control library
 *Author:    Simon
 *
 *DESCRIPTION
 *      Initializes the ADC for sensor reading and the port for LED control.
 *	   ADC data is read using the ReadADC library.
 *	   
 *	   Includes functions for automatically controlling the LED depending
 *	   on Photocell reading, and functions for manually controlling the LED
 *	   
 *	   ADC and PORT configurations can be set in the include SunDetect.h
 *      
*/


#include <util/delay.h>
#include <avr/io.h>
#include "SunDetect.h"
#include "ReadADC.h"
#define F_CPU 16000000UL

/// Setup for ADC reading and datadirection for the LED port
void SD_init(void)
{
	//ADC0 CONFIG
	ADMUX |= (1<<REFS0);
	DIDR0 |= (1<<SD_ADCDIGITAL);
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	//PORTA CONFIG
	LIGHTDDR = (1<<LIGHTPORT0);
}


/// Calls the ReadADC library with the current ADC pin as parameter
int readLight()
{
	return readADC(SD_MUXINIT);
}

/**
Toggles the LED based on the configured minimum lighting level.
*/
void lightToggle(int lightValue)
{
	if (lightValue < LIGHTMINIMUM)
	{
		LIGHTPORT |= (1<<LIGHTPORT0);
	}
	else
	{
		LIGHTPORT &= ~(1<<LIGHTPORT0);
	}
}
/**
Toggles the LED on/off
*/
void lightSwitch()
{
	if (LIGHTPORT & (1<<LIGHTPORT0))
	{
		LIGHTPORT &= ~(1<<LIGHTPORT0);
	}
	else
	{
		LIGHTPORT |= (1<<LIGHTPORT0);
	}
}