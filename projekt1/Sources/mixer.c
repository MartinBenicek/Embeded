/*
 * mixer.c
 *
 *  Created on: 21. 10. 2024
 *      Author: m_benicek, s_bucka
 */

#include "MKL25Z4.h"



#define MIX_PIN	0	// Switch_pin 22 = D0
#define SV1_PIN	5	// SV1_PIN 11 = E5
#define SV2_PIN	1	// SV2_PIN 12 = C1
#define SV3_PIN	4	// SV3_PIN 13 = E4
#define SV4_PIN	0	// SV4_PIN 15 = E0
#define SV5_PIN	1	// SV5_PIN 16 = E1

#define H1_PIN 	3	// H1 24 = D3
#define H2_PIN 	16	// H2 28 = C16
#define H3_PIN 	2	// H3 23 = D2
#define H4_PIN 	5	// H4 34 = C5
#define H5_PIN 	4	// H5 26 = D4
#define H6_PIN 	7	// H6 36 = C7
#define H7_PIN 	5	// H7 25 = D5
#define H8_PIN 	6	// H8 33 = C6


void init(void)
{
	// Enable clock for ports A, B, C, D, E
	SIM->SCGC5 |= (	SIM_SCGC5_PORTA_MASK | 
					SIM_SCGC5_PORTB_MASK |
					SIM_SCGC5_PORTC_MASK |
					SIM_SCGC5_PORTD_MASK |
					SIM_SCGC5_PORTE_MASK );
	
	// Set pin function to GPIO
	PORTD->PCR[MIX_PIN] = PORT_PCR_MUX(1);

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
	PTD->PDDR |= (1 << MIX_PIN);

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

void MIXER_NastavVentil(uint8_t valve_pin, uint8_t state) {
    // Nasatveni ventilu na danem pinu
    if (valve_pin == SV1_PIN || valve_pin == SV3_PIN || valve_pin == SV4_PIN || valve_pin == SV5_PIN) {
        if (state) {
            PTE->PSOR = (1 << valve_pin);	// Otevreni ventilu
        } else {
            PTE->PCOR = (1 << valve_pin);	// Zavreni ventilu
        }
    } else if (valve_pin == SV2_PIN) {
        if (state) {
            PTC->PSOR = (1 << valve_pin); 	// Otevreni ventilu
        } else {
            PTC->PCOR = (1 << valve_pin);  // Zavreni ventilu
        }
    }
}

uint8_t MIXER_SledovatHladinu(uint8_t sensor_pin) {
    // Sledovani hladiny na senzoru
    uint8_t value = 0;
    if (sensor_pin == H1_PIN || sensor_pin == H3_PIN || 
		sensor_pin == H5_PIN || sensor_pin == H7_PIN) {
        value = (PTD->PDIR & (1 << sensor_pin)) ? 1 : 0;	// 1 = hladina je na senzoru | 0 = hladina neni na senzoru
    } else if (sensor_pin == H2_PIN || sensor_pin == H4_PIN || 
			   sensor_pin == H6_PIN || sensor_pin == H8_PIN) {
        value = (PTC->PDIR & (1 << sensor_pin)) ? 1 : 0;	// 1 = hladina je na senzoru | 0 = hladina neni na senzoru
    }
    return value;
}

void MIXER_NastavMichadlo(uint8_t state){
	if(state){
		PTD->PSOR = PTD->PSOR |(1 << MIX_PIN);
	} else{
		PTD->PCOR = PTD->PCOR |(1 << MIX_PIN);
	}
}



static inline int IsKeyPressed(uint8_t pin)
{
	if ((PTA->PDIR & (1 << pin)) == 0)
		return 1;
	else
		return 0;
}
