/*
 * TempDetect.c
 *
 * Created: 29/05/2019 12.30.04
 *  Author: Simon
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <math.h>
#include "TempDetect.h"
#include <ReadADC.h>

void TD_init()
{
	ADMUX |= (1<<REFS0);
	DIDR0 |= (1<<TD_ADCDIGITAL);
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}
float readTemp()
{
	return convertADC(readADC(TD_MUXINIT));
}
float readTempCelsius()
{
	return readTempKelvin() - 273.15;
}
float readTempKelvin()
{
	float temp = readTemp();
	return 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp)) * temp);
}
float readTempFahrenheit()
{
	return readTempKelvin() * (9.0 / 5.0) - 459.67;
}
float convertADC(int ADC_data)
{
	return log(10000.0 * ((1024.0 / ADC_data) - 1));
}