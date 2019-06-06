/*
 * MatrixKeyboard.h
 *
 * Created: 03/06/2019 12.31.01
 *  Author: Simon
 */ 


#ifndef MATRIXKEYBOARD_H_
#define MATRIXKEYBOARD_H_

#define DDRx DDRK
#define PORTx PORTK
#define Px0 PK0
#define Px1 PK1
#define Px2 PK2
#define Px3 PK3
#define OCRnA OCR4A
#define OCRnB OCR4B
#define TCCRnB TCCR4B
#define TIMSKn TIMSK4
#define OCIEnA OCIE4A
#define OCIEnB OCIE4B
#define CSn2 CS42
#define CSn1 CS41
#define CSn0 CS40
#define WGMn2 WGM42

#define ROWPIN PINK
#define ROWPIN1 PINK7
#define ROWPIN2 PINK6
#define ROWPIN3 PINK5
#define ROWPIN4 PINK4

#define COLPORT PORTK
#define COL4 0b00001110
#define COL3 0b00001101
#define COL2 0b00001011
#define COL1 0b00000111

int columnScan();
void MK_init();
int readRow();
char keyDecode(int activePort, int activeRow);


#endif /* MATRIXKEYBOARD_H_ */