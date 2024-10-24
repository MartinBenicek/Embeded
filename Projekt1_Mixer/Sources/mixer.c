/*
 * mixer.c
 *
 *  Created on: 23. 10. 2023
 *      Author: student
 */
#include "MKL25Z4.h"
#include "mixer.h"

static int valvePins[] = {0, 5, 1, 4, 0, 1};
static int hladinaPins[] = {3, 16, 2, 5, 4, 7, 5, 6};


void mixer_init() {
	// hodinový signál pro porty
	SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK
			| SIM_SCGC5_PORTC_MASK
			| SIM_SCGC5_PORTE_MASK
			| SIM_SCGC5_PORTD_MASK );

	// nastavení pio módu (ventilù)
	PORTE->PCR[valvePins[SV1]] = PORT_PCR_MUX(1);
	PORTC->PCR[valvePins[SV2]] = PORT_PCR_MUX(1);
	PORTE->PCR[valvePins[SV3]] = PORT_PCR_MUX(1);
	PORTE->PCR[valvePins[SV4]] = PORT_PCR_MUX(1);
	PORTE->PCR[valvePins[SV5]] = PORT_PCR_MUX(1);

	// nastavení pio módu (mixer)
	PORTD->PCR[valvePins[MIXER]] = PORT_PCR_MUX(1);

	// nastavení pio módu (hladin)
	PORTD->PCR[hladinaPins[H1]] = PORT_PCR_MUX(1);
	PORTC->PCR[hladinaPins[H2]] = PORT_PCR_MUX(1);
	PORTD->PCR[hladinaPins[H3]] = PORT_PCR_MUX(1);
	PORTC->PCR[hladinaPins[H4]] = PORT_PCR_MUX(1);
	PORTD->PCR[hladinaPins[H5]] = PORT_PCR_MUX(1);
	PORTC->PCR[hladinaPins[H6]] = PORT_PCR_MUX(1);
	PORTD->PCR[hladinaPins[H7]] = PORT_PCR_MUX(1);
	PORTC->PCR[hladinaPins[H8]] = PORT_PCR_MUX(1);

	// nastavení smìrù ventilù
	PTE->PDDR |= (1 << valvePins[SV1]);
	PTC->PDDR |= (1 << valvePins[SV2]);
	PTE->PDDR |= (1 << valvePins[SV3]);
	PTE->PDDR |= (1 << valvePins[SV4]);
	PTE->PDDR |= (1 << valvePins[SV5]);

	// nastavení smìrù mixéru
	PTD->PDDR |= (1 << valvePins[MIXER]);

	// nastavení smìrù indikátiorù hladin
	PTD->PDDR &= ~(1 << hladinaPins[H1]);
	PTC->PDDR &= ~(1 << hladinaPins[H2]);
	PTD->PDDR &= ~(1 << hladinaPins[H3]);
	PTC->PDDR &= ~(1 << hladinaPins[H4]);
	PTD->PDDR &= ~(1 << hladinaPins[H5]);
	PTC->PDDR &= ~(1 << hladinaPins[H6]);
	PTD->PDDR &= ~(1 << hladinaPins[H7]);
	PTC->PDDR &= ~(1 << hladinaPins[H8]);

	// nastavení pùvodní hodnoty ventilù
	mixer_valveClose(valvePins[SV1]);
	mixer_valveClose(valvePins[SV2]);
	mixer_valveClose(valvePins[SV3]);
	mixer_valveClose(valvePins[SV4]);
	mixer_valveClose(valvePins[SV5]);


	// nastavení pullup a pulldown rezistorù
	PORTD->PCR[hladinaPins[H1]] |= (PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);
	PORTC->PCR[hladinaPins[H2]] |= (PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);
	PORTD->PCR[hladinaPins[H3]] |= (PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);
	PORTC->PCR[hladinaPins[H4]] |= (PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);
	PORTD->PCR[hladinaPins[H5]] |= (PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);
	PORTC->PCR[hladinaPins[H6]] |= (PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);
	PORTD->PCR[hladinaPins[H7]] |= (PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);
	PORTC->PCR[hladinaPins[H8]] |= (PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);

}


void mixer_valveOpen(int valve){
	if(valve == SV2){
		PTC->PSOR |= (1 << valvePins[valve]);
		return;
	}

	PTE->PSOR |= (1 << valvePins[valve]);

}

void mixer_valveClose(int valve){
	if(valve == SV2){
		PTC->PCOR |= (1 << valvePins[valve]);
		return;
	}

	PTE->PCOR |= (1 << valvePins[valve]);
}

// vyzkoušet
void mixer_mixerStart() {
	PTD->PSOR |= (1 << valvePins[MIXER]);
}

void mixer_mixerStop() {
	PTD->PCOR |= (1 << valvePins[MIXER]);
}

int mixer_isReached(int hladina)
{
	if(hladina % 2 == 0) {
		if ((~PTD->PDIR & (1 << hladinaPins[hladina])) == 0)
			return 1;
		return 0;
	}
	if ((~PTC->PDIR & (1 << hladinaPins[hladina])) == 0)
		return 1;
	return 0;
}

double mixer_getTimeNeeded(int hladina)
{
	if(hladina == H3 || hladina == H5 || hladina == H8)
		return 4.7;
	if(hladina == H2 || hladina == H7)
		return 9.5;
	return 14.0;
}

