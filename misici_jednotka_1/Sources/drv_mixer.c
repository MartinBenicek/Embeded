/*
 * drv_mixer.c
 *
 *  Created on: 1. 11. 2024
 *      Author: student
 */

#include "MKL25Z4.h"
#include "drv_mixer.h"

#define PIN_SV2	(1)
#define PIN_mix	(0)
#define PIN_SV4	(0)
#define PIN_SV5	(1)
#define PIN_SV3	(4)
#define PIN_SV1	(5)

#define PIN_H4	(5)
#define PIN_H8	(6)
#define PIN_H6	(7)
#define PIN_H2	(16)
#define PIN_H3	(2)
#define PIN_H1	(3)
#define PIN_H5	(4)
#define PIN_H7	(5)

void MIXER_Init(void){

	// Enable clock for C,D,E
	SIM->SCGC5 |= (SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK);

	// set MUX to 1 (GPIO)
	PORTC->PCR[PIN_SV2] = PORT_PCR_MUX(1);
	PTC->PDDR |= (1 << PIN_SV2);		/* set direction to output */

	PORTD->PCR[PIN_mix] = PORT_PCR_MUX(1);
	PTD->PDDR |= (1 << PIN_mix);

	PORTE->PCR[PIN_SV4] = PORT_PCR_MUX(1);
	PTE->PDDR |= (1 << PIN_SV4);

	PORTE->PCR[PIN_SV5] = PORT_PCR_MUX(1);
	PTE->PDDR |= (1 << PIN_SV5);

	PORTE->PCR[PIN_SV3] = PORT_PCR_MUX(1);
	PTE->PDDR |= (1 << PIN_SV3);

	PORTE->PCR[PIN_SV1] = PORT_PCR_MUX(1);
	PTE->PDDR |= (1 << PIN_SV1);


	PORTC->PCR[PIN_H4] = PORT_PCR_MUX(1);
	PTC->PDDR &= ~(1 << PIN_H4);				/* set direction to input*/
	PORTC->PCR[PIN_H4] &= ~PORT_PCR_PE_MASK; 	/* disable pull resistor */

	PORTC->PCR[PIN_H8] = PORT_PCR_MUX(1);
	PTC->PDDR &= ~(1 << PIN_H8);
	PORTC->PCR[PIN_H8] &= ~PORT_PCR_PE_MASK;

	PORTC->PCR[PIN_H6] = PORT_PCR_MUX(1);
	PTC->PDDR &= ~(1 << PIN_H6);
	PORTC->PCR[PIN_H6] &= ~PORT_PCR_PE_MASK;

	PORTC->PCR[PIN_H2] = PORT_PCR_MUX(1);
	PTC->PDDR &= ~(1 << PIN_H2);
	PORTC->PCR[PIN_H2] &= ~PORT_PCR_PE_MASK;

	PORTD->PCR[PIN_H3] = PORT_PCR_MUX(1);
	PTD->PDDR &= ~(1 << PIN_H3);
	PORTD->PCR[PIN_H3] &= ~PORT_PCR_PE_MASK;

	PORTD->PCR[PIN_H1] = PORT_PCR_MUX(1);
	PTD->PDDR &= ~(1 << PIN_H1);
	PORTD->PCR[PIN_H1] &= ~PORT_PCR_PE_MASK;

	PORTD->PCR[PIN_H5] = PORT_PCR_MUX(1);
	PTD->PDDR &= ~(1 << PIN_H5);
	PORTD->PCR[PIN_H5] &= ~PORT_PCR_PE_MASK;

	PORTD->PCR[PIN_H7] = PORT_PCR_MUX(1);
	PTD->PDDR &= ~(1 << PIN_H7);
	PORTD->PCR[PIN_H7] &= ~PORT_PCR_PE_MASK;

}

/* Set value for given pin */
void mixerVystup(MIXER_pin pin, uint8_t value )
{

	uint8_t pin2;

	switch(pin)
	{
		case SV2: pin2 = PIN_SV2;
			if ( value )
				PTC->PSOR |= (1 << (uint8_t)pin2);  /* set pin to HIGH  */
			else
				PTC->PCOR |= (1 << (uint8_t)pin2);  /* clear pin (set LOW)  */
			break;

		case mix: pin2 = PIN_SV2;
			if ( value )
				PTD->PSOR |= (1 << (uint8_t)pin2);  /* set pin to HIGH  */
			else
				PTD->PCOR |= (1 << (uint8_t)pin2);  /* clear pin (set LOW)  */
			break;

		case SV4: pin2 = PIN_SV4;
			if ( value )
				PTE->PSOR |= (1 << (uint8_t)pin2);  /* set pin to HIGH  */
			else
				PTE->PCOR |= (1 << (uint8_t)pin2);  /* clear pin (set LOW)  */
			break;
		case SV5: pin2 = PIN_SV5;
			if ( value )
				PTE->PSOR |= (1 << (uint8_t)pin2);  /* set pin to HIGH  */
			else
				PTE->PCOR |= (1 << (uint8_t)pin2);  /* clear pin (set LOW)  */
			break;
		case SV3: pin2 = PIN_SV3;
			if ( value )
				PTE->PSOR |= (1 << (uint8_t)pin2);  /* set pin to HIGH  */
			else
				PTE->PCOR |= (1 << (uint8_t)pin2);  /* clear pin (set LOW)  */
			break;
		case SV1: pin2 = PIN_SV1;
			if ( value )
				PTE->PSOR |= (1 << (uint8_t)pin2);  /* set pin to HIGH  */
			else
				PTE->PCOR |= (1 << (uint8_t)pin2);  /* clear pin (set LOW)  */
			break;

		default:
			while(1) ;	/* Error: invalid pin! */
	}
}

uint8_t hladinaRead(MIXER_pin pin){

	uint8_t pin2;
	uint8_t retVal = LOW;

	switch(pin){
		case H4: pin2 = PIN_H4;
			break;
		case H8: pin2 = PIN_H8;
			break;
		case H6: pin2 = PIN_H6;
			break;
		case H2: pin2 = PIN_H2;
			break;
		case H3: pin2 = PIN_H3;
			break;
		case H1: pin2 = PIN_H1;
			break;
		case H5: pin2 = PIN_H5;
			break;
		case H7: pin2 = PIN_H7;
			break;
		default:
			while(1) ;	/* Error: invalid pin! */
	}

	switch(pin){

		case H4:
		case H8:
		case H6:
		case H2:
			if ((PTC->PDIR & (1 << (uint8_t)pin2)) == 0)
				retVal = LOW;
			else
				retVal = HIGH;
			break;

		case H3:
		case H1:
		case H5:
		case H7:
			if ((PTD->PDIR & (1 << (uint8_t)pin2)) == 0)
				retVal = LOW;
			else
				retVal = HIGH;
			break;

	}

	return retVal;

}
