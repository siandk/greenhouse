/*
 * SunDetect.h
 *
 * Created: 29/05/2019 12.22.04
 *  Author: Simon
 */ 

#include <avr/io.h>

#ifndef SUNDETECT_H_
#define SUNDETECT_H_

#define SD_MUXINIT 0b00000000	/**< MUX value for the chosen ADC pin. See table 26-4          */
#define SD_ADCDIGITAL ADC0D		/**< Digital ADC#. For power saving          */

#define LIGHTPORT PORTA			/**< The port used for the LED light         */
#define LIGHTPORT0 PA0			/**< Output used for the LED light          */
#define LIGHTDDR DDRA			/**< Data direction register for LED light        */

#define LIGHTMINIMUM 200		/**< Minimum ADC value, before the LED is automatically switched on/off          */

void SD_init();
int readLight();
void lightToggle(int lightValue);
void lightSwitch();



#endif /* SUNDETECT_H_ */