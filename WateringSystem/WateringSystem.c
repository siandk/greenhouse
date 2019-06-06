/*
 * WateringSystem.c
 *
 * Created: 29/05/2019 12.59.06
 *  Author: Simon
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "WateringSystem.h"

void WS_init()
{
	WS_DDRx1 |= (1<<WS_Px0) | (1<<WS_Px1) | (1<<WS_Px2) | (1<<WS_Px3);
	
	WS_TCCRnA |= (1<<WS_COMnx1); // Clear on compare match
	WS_TCCRnB |= (1<<WGM33); // Phase and frequency correct mode
	WS_TCCRnB |= (1<<CS31); // Prescaler /8
	WS_ICRn = 20000; // TOP = fclk / (2 * N * hz)  |  16e6 / (2 * 8 * 50) = 20000
	WS_DDRx2 |= (1<<WS_Pxn);
}
void openWater()
{
	WS_OCRnx = 2000;
}
void closeWater()
{
	WS_OCRnx = 1000;
}
void waterToggle()
{
	if (WS_OCRnx == 2000)
	{
		closeWater();
	}
	else
	{
		openWater();
	}
}
void start()
{
	openWater();
	moveForward();
	moveBackward();
	closeWater();
}

void moveForward()
{
	int i;
	for (i = 0; i < REV * REVDISTANCE; i++)
	{
		rotateClockwise();
	}
	WS_PORTx = 0x00;
}
void rotateClockwise()
{
	WS_PORTx = (1<<WS_Px0);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px0) | (1<<WS_Px1);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px1);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px1) | (1<<WS_Px2);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px2);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px2) | (1<<WS_Px3);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px3);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px3) | (1<<WS_Px0);
	_delay_ms(MOVEDELAY);
}
void moveBackward()
{
	int i;
	for (i = 0; i < REV * REVDISTANCE; i++)
	{
		rotateCounterClockwise();
	}
	WS_PORTx = 0x00;
}
void rotateCounterClockwise()
{
	WS_PORTx = (1<<WS_Px3);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px3) | (1<<WS_Px2);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px2);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px2) | (1<<WS_Px1);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px1);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px1) | (1<<WS_Px0);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px0);
	_delay_ms(MOVEDELAY);
	WS_PORTx = (1<<WS_Px0) | (1<<WS_Px3);
	_delay_ms(MOVEDELAY);
}