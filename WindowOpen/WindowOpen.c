/*
 * WindowOpen.c
 *
 * Created: 29/05/2019 12.48.25
 *  Author: Simon
 */ 

#include <avr/io.h>
#include "WindowOpen.h"

void WO_init()
{
	WO_TCCRnA |= (1<<WO_COMnx1);
	WO_TCCRnB |= (1<<WGMn3);
	WO_TCCRnB |= (1<<CS31);
	WO_ICRn = 20000;
	WO_DDRx |= (1<<WO_Pxn);
}
void openWindow(float currentTemp)
{
	if (currentTemp > OPENAT)
	{
		WO_OCRnx = 2000;
	}
	if (currentTemp < CLOSEAT)
	{
		WO_OCRnx = 1000;
	}
}
void windowToggle()
{
	if (WO_OCRnx == 2000)
	{
		WO_OCRnx = 1000;
	}
	else
	{
		WO_OCRnx = 2000;
	}
}