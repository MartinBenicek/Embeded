/*
 * mixer.c
 *
 *  Created on: 21. 10. 2024
 *      Author: m_benicek
 */

#include "MKL25Z4.h"

#define SWITCH_PIN 22
#define SV1_PIN 11
#define SV2_PIN 12
#define SV3_PIN 13
#define SV4_PIN 15
#define SV5_PIN 16
#define H1_PIN 24
#define H2_PIN 28
#define H3_PIN 23
#define H4_PIN 34
#define H5_PIN 26
#define H6_PIN 36
#define H7_PIN 25
#define H8_PIN 33

void init(void)
{
	// Enable clock for ports A, B, C, D, E
	SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK |
			SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK );
	// Set pin function to GPIO
	PORTD->PCR[SWITCH_PIN] = PORT_PCR_MUX(1);

	PORTE->PCR[SV1_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[SV2_PIN] = PORT_PCR_MUX(1);
	PORTE->PCR[SV3_PIN] = PORT_PCR_MUX(1);
	PORTE->PCR[SV4_PIN] = PORT_PCR_MUX(1);
	PORTE->PCR[SV5_PIN] = PORT_PCR_MUX(1);

	PORTD->PCR[H1_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[H2_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[H3_PIN] = PORT_PCR_MUX(1);
	/*
	PORTC->PCR[H4_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[H5_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[H6_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[H7_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[H8_PIN] = PORT_PCR_MUX(1);
*/

	// Set pin direction

	//Switch is output
	PTD->PDDR |= (1 << SWITCH_PIN);

	// SV1-SV5 is output
	PTE->PDDR |= (1 << SV1_PIN);
	PTC->PDDR |= (1 << SV2_PIN);
	PTE->PDDR |= (1 << SV3_PIN);
	PTE->PDDR |= (1 << SV4_PIN);
	PTE->PDDR |= (1 << SV5_PIN);

	// Hx are inputs (sensors)
	PTD->PDDR &= ~(1 << H1_PIN);
	PTC->PDDR &= ~(1 << H2_PIN);
	PTD->PDDR &= ~(1 << H3_PIN);
	/*
	PTC->PDDR &= ~(1 << H4_PIN);
	PTD->PDDR &= ~(1 << H5_PIN);
	PTC->PDDR &= ~(1 << H6_PIN);
	PTD->PDDR &= ~(1 << H7_PIN);
	PTC->PDDR &= ~(1 << H8_PIN);*/
}

void MIXER_NastavVentil(ventil, state){
	if ( state )
		PTE->PSOR |= (1 << (uint8_t)ventil);  /* set pin to HIGH  */
	else
		PTE->PCOR |= (1 << (uint8_t)ventil);  /* clear pin (set LOW)  */
}

void MIXER_SledovatHladinu(int sensor){
	PTE->PSOR |= (1 << (uint8_t)sensor);  /* set pin to HIGH  */
	PTE->PCOR |= (1 << (uint8_t)sensor);  /* clear pin (set LOW)  */
}

