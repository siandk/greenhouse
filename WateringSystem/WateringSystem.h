/*
 * WateringSystem.h
 *
 * Created: 29/05/2019 12.59.19
 *  Author: Simon
 */ 

#include <avr/io.h>

#ifndef WATERINGSYSTEM_H_
#define WATERINGSYSTEM_H_


// STEP MOTOR CONFIG

				// 4096 steps for a full revolution according to datasheet.
#define REV 512 // How many function runs for a full revolution of the stepmotor at 8 steps per run. 4096 / 8 = 512				
#define REVDISTANCE 5  // How many revs untill the full length of the watering system has been run

#define WS_PORTx PORTB
#define WS_DDRx1 DDRB
#define WS_Px0 PB0
#define WS_Px1 PB1
#define WS_Px2 PB2
#define WS_Px3 PB3
#define MOVEDELAY 1 // Delay between steps


// SERVO MOTOR CONFIG
#define WS_TCCRnA TCCR3A
#define WS_TCCRnB TCCR3B
#define WS_ICRn ICR3
#define WS_DDRx2 DDRE
#define WS_Pxn PE5
#define WS_OCRnx OCR3C
#define WS_COMnx1 COM3C1

void WS_init();
void openWater();
void closeWater();
void waterToggle();
void start();
void moveForward();
void rotateClockwise();
void moveBackward();
void rotateCounterClockwise();



#endif /* WATERINGSYSTEM_H_ */