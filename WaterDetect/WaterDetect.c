/*
 * WaterDetect.c
 *
 * Created: 29/05/2019 12.42.50
 *  Author: Simon
 */
#define F_CPU 16000000UL
#include <util/delay.h>
#include "WaterDetect.h"
#include <ReadADC.h>
#include <avr/io.h>

void WD_init()
{
	ADMUX |= (1<<REFS0);
	DIDR0 |= (1<<WD_ADCDIGITAL);
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
}
int waterOK()
{
	if (readLevel() > WATERLIMIT)
	{
		return 1;
	}
	return 0;
}

int readLevel()
{
	return readADC(WD_MUXINIT);
}