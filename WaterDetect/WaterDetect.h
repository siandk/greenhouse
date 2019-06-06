/*
 * WaterDetect.h
 *
 * Created: 29/05/2019 12.43.03
 *  Author: Simon
 */ 
#include <avr/io.h>

#ifndef WATERDETECT_H_
#define WATERDETECT_H_

// ADC3
#define WD_MUXINIT 0b00000011
#define WD_ADCDIGITAL ADC3D

// Values
#define WATERLIMIT 220

extern void WD_init();
extern int waterOK();
extern int readLevel();



#endif /* WATERDETECT_H_ */