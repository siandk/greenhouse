/*
 * WindowOpen.h
 *
 * Created: 29/05/2019 12.48.38
 *  Author: Simon
 */ 

#include <avr/io.h>

#ifndef WINDOWOPEN_H_
#define WINDOWOPEN_H_


// Timer 3
#define WO_TCCRnA TCCR3A
#define WO_TCCRnB TCCR3B
#define WO_ICRn ICR3
#define WO_DDRx DDRE
#define WO_Pxn PE4
#define WO_OCRnx OCR3B
#define WO_COMnx1 COM3B1
#define WGMn3 WGM33

// Values
#define OPENAT 24
#define CLOSEAT 23

void WO_init();
void openWindow(float currentTemp);
void windowToggle();

#endif /* WINDOWOPEN_H_ */