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