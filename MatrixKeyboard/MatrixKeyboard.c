/*
 * MatrixKeyboard.c
 *
 * Created: 03/06/2019 12.29.53
 * Author : Simon
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "MatrixKeyboard.h"


void MK_init()
{
	// Set data direction
	DDRx = (1<<Px0) | (1<<Px1) | (1<<Px2) | (1<<Px3);
	PORTx = 0xFE; // Initial port configuration (Start reading on port 0x01)
	
	// Keyboard scan timer. Current timer compare value found by trial and error
	OCRnA = 64000;
	OCRnB = 32000; // 51200 25600 12800 6400 3200
	TCCRnB |= (1<<CSn1) | (1<<CSn0) | (1<<WGMn2); // /64 prescaler see table 17-6
	// Enable interrupt for output compare OCRnA & OCRnB
	TIMSKn |= (1<<OCIEnA) | (1<<OCIEnB);
	
	
	sei();
}
int readRow()
{
	if (!(ROWPIN & (1<<ROWPIN1)))
	{
		return 0;
	}
	if (!(ROWPIN & (1<<ROWPIN2)))
	{
		return 1;
	}
	if (!(ROWPIN & (1<<ROWPIN3)))
	{
		return 2;
	}
	if (!(ROWPIN & (1<<ROWPIN4)))
	{
		return 3;
	}
	return 9;
}
uint8_t bits[] = {COL1, COL2, COL3, COL4};

int columnScan()
{
	uint8_t setPort;
	int i;
	setPort = COLPORT & 0b11110000;
	for (i = 0; i < 4; i++)
	{
		if (COLPORT == (setPort | bits[i]))
		{
			if (i == 3)
			{
				COLPORT = setPort | bits[0];
				return 0;
			}
			else {
				COLPORT = setPort | bits[i + 1];
				return i + 1;
			}
		}
	}
}

char keyboard[4][5] = {"123A", "456B", "789C", "*0#D"};

char keyDecode(int activePort, int activeRow)
{
	if (activeRow > 3 || activeRow < 0)
	{
		return 0x00;
	}
	return keyboard[activeRow][activePort];
}

