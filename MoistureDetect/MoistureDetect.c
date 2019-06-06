/*
 * MoistureDetect.c
 *
 * Created: 04/06/2019 08.24.07
 * Author : Simon
 */ 

#include <avr/io.h>
#include <ReadADC.h>
#include "MoistureDetect.h"


/* Replace with your library code */

void MD_init()
{
	//ADC2 CONFIG
	ADMUX |= (1<<REFS0);
	DIDR0 |= (1<<MD_ADCDIGITAL);
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}
int readMoisture()
{
	return readADC(MD_MUXINIT);
}
int moistureOK(int moisture)
{
	if (moisture > MOISTURELIMIT)
	{
		return 1;
	}
	return 0;
}