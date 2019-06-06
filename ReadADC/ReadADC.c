/*
 * ReadADC.c
 *
 * Created: 03/06/2019 09.39.53
 *  Author: Simon
 */ 

#include <avr/io.h>
#include "ReadADC.h"

int readADC(int MUX)
{
	// Choose ADC pin to read
	setMUX(MUX);
	// Start ADC reading 
	ADCSRA |= (1<<ADSC);
	// Wait for reading to finish
	while (ADCSRA & (1<<ADSC))
	{		
	}
	// Return ADC value
	if (VREF == 3.3)
	{
		// All sensor reading formulas are set up using a 5v reference.
		// I did not have time to change the formulas so this will have to do
		// 5V   / 1024 = 4.88mV
		// 3.3V / 1024 = 3.22mV
		// 4.88 / 3.22 = 1.515
		return ADC * 1.515;
	}
	return ADC;
}
void setMUX(int MUX)
{
	// Reset MUX
	char MUX_conf = ADMUX & 0b11111000;
	// Set MUX
	MUX_conf |= MUX;
	ADMUX = MUX_conf;
}