/*
 * ManualControl.c
 *
 * Created: 03/06/2019 12.29.03
 * Author : Simon
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "SunDetect.h"
#include "WindowOpen.h"
#include "WateringSystem.h"


int ManualControl(char command)
{
	switch (command)
	{
		case '1':
			lightSwitch();
			return 0;
			
		case '2':
			windowToggle();
			return 0;
			
		case '3':
			if(WS_PORTx & 0x00)
			{
				printf("Watering already running\n\r");
				return 0;
			}
			else
			{
				printf("Starting watering system\n\r");
				return 1;
			}
						
		default:
			return 0;
	}
}

