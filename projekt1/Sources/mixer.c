/*
 * mixer.c
 *
 *  Created on: 21. 10. 2024
 *      Author: m_benicek, s_bucka
 */

#include "MKL25Z4.h"


//Switch_pin 22 = D0
#define SWITCH_PIN 0
//SV1_PIN 11 = E5
#define SV1_PIN 5
//SV2_PIN 12 = C1
#define SV2_PIN 1
//SV3_PIN 13 = E4
#define SV3_PIN 4
//SV4_PIN 15 = E0
#define SV4_PIN 0
//SV5_PIN 16 = E1
#define SV5_PIN 1
//H1 24 = D3
#define H1_PIN 3
//H2 28 = C16
#define H2_PIN 16
//H3 23 = D2
#define H3_PIN 2
//H4 34 = C5
#define H4_PIN 5
//H5 26 = D4
#define H5_PIN 4
//H6 36 = C7
#define H6_PIN 7
//H7 25 = D5
#define H7_PIN 5
//H8 33 = C6
#define H8_PIN 6


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
	PORTC->PCR[H4_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[H5_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[H6_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[H7_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[H8_PIN] = PORT_PCR_MUX(1);

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
	PTC->PDDR &= ~(1 << H4_PIN);
	PTD->PDDR &= ~(1 << H5_PIN);
	PTC->PDDR &= ~(1 << H6_PIN);
	PTD->PDDR &= ~(1 << H7_PIN);
	PTC->PDDR &= ~(1 << H8_PIN);
}

void MIXER_NastavVentil(ventil, state){
	if (state == 1){
		if(ventil == 1){
				PTC->PSOR |= (1 << ventil);
				return;
			}
		PTE->PSOR |= (1 << ventil);
	} else{
		if(ventil == 1){
			PTC->PCOR |= (1 << ventil);
			return;
		}

		PTE->PCOR |= (1 << ventil);
	}
}

void MIXER_SledovatHladinu(int sensor){
	PTE->PSOR |= (1 << (uint8_t)sensor);  /* set pin to HIGH  */
	PTE->PCOR |= (1 << (uint8_t)sensor);  /* clear pin (set LOW)  */
}

