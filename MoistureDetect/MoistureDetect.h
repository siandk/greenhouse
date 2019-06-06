/*
 * MoistureDetect.h
 *
 * Created: 04/06/2019 08.26.35
 *  Author: Simon
 */ 


#ifndef MOISTUREDETECT_H_
#define MOISTUREDETECT_H_

// ADC2
#define MD_MUXINIT 0b00000010	// Value for starting MUX
#define MD_ADCDIGITAL ADC2D		// Digital ADC# for power saving

#define MOISTURELIMIT 800

void MD_init();
int readMoisture();
int moistureOK(int moisture);

#endif /* MOISTUREDETECT_H_ */