/*
 * TempDetect.h
 *
 * Created: 29/05/2019 12.30.16
 *  Author: Simon
 */ 

#include <avr/io.h>

#ifndef TEMPDETECT_H_
#define TEMPDETECT_H_

// ADC1
#define TD_MUXINIT 0b00000001
#define TD_ADCDIGITAL ADC1D

extern void TD_init();
float readTempCelsius();
float readTempKelvin();
float readTempFahrenheit();
float convertADC(int ADC_data);
float readTemp();


#endif /* TEMPDETECT_H_ */