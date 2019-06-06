/*
 * GreenhouseInit.c
 *
 * Created: 29/05/2019 11.59.02
 *  Author: Simon
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "stdio_setup.h"
#include "GreenhouseInit.h"
#include "WindowOpen.h"
#include "SunDetect.h"
#include "TempDetect.h"
#include "WateringSystem.h"
#include "WaterDetect.h"
#include "MatrixKeyboard.h"
#include "MoistureDetect.h"
#include "lcd.h"
#include <avr/wdt.h>

void GreenhouseInit()
{
	// Initialization of components
	UartInit();
	WO_init();
	SD_init();
	TD_init();
	WS_init();
	WD_init();
	MK_init();
	MD_init();
	
	// Turn on LCD display
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	
	// TIMER 1 CONFIG
	
	// Set /1024 prescaler, CTC Mode - See table 17-6 & 17.11.5
	TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);
	// Enable interrupt for output compare OCR1A
	TIMSK1 |= (1<<OCIE1A);
	
	// 2 second delay
	OCR1A = 31249;
	
	sei();
	
	// Relay port config
	DDRJ |= (1<<PJ1);
	
	// Enable watchdog timer (4 second timeout)
	wdt_enable(WDTO_4S);
}