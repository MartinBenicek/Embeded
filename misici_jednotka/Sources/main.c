/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "drv_systick.h"
#include "drv_gpio.h"
#include "drv_lcd.h"

/*
 E5 11 Ventil SV1
 C1 12 Ventil SV2
 E4 13 Ventil SV3
 E0 15 Ventil SV4
 E1 16 Ventil SV5

 E3 14 Nezapojeno
 B1 21 Nezapojeno

 D0 22 Míchadlo v mísicí nádrži

 D3 24 Hladinomìr H1
 C16 28 Hladinomìr H2
 D2 23 Hladinomìr H3
 C5 34 Hladinomìr H4
 D4 26 Hladinomìr H5
 C7 36 Hladinomìr H6
 D5 25 Hladinomìr H7
 C6 33 Hladinomìr H8

 */
// Definovani hodnot pinu na jednotlive promenne
#define SWITCH_PIN (4) // A4
#define SWITCH_PIN_2 (5) // A5

#define SV1_PIN (5) // E5
#define SV2_PIN (1) // C1
#define SV3_PIN (4) // E4
#define SV4_PIN (0) // E0
#define SV5_PIN (1) // E1

#define H1_PIN (3) //  D3
#define H2_PIN (16) // C16
#define H3_PIN (2) //  D2
#define H4_PIN (5) //  C5
#define H5_PIN (4) //  D4
#define H6_PIN (7) //  C7
#define H7_PIN (5) //  D5
#define H8_PIN (6) //  C6

#define MIX_PIN (0) // D0

// Definice naplneni nadrzi
#define CTVRT_NADRZE (1)
#define PUL_NADRZE (2)
#define CELA_NADRZ (3)

static int i = 0;
// Enum pro faze ve switchi
typedef enum {start, nadrz1, nadrz2, nadrz3, mix, vylevani} FAZE;
// Promenne, dle kterych se zaplnuji jednotlive nadrze
int tank1 = PUL_NADRZE;
int tank2 = CELA_NADRZ;
int tank3 = PUL_NADRZE;
// Nastaveni vychozi hodnoty
FAZE valve = start;
// Prototype
void init(void);
static inline int IsKeyPressed(int pin);

int main(void) {
	init(); // Inicializace pinu, portu
	SYSTICK_initialize(); // Inicializace knihovny SYSTICK
	LCD_initialize(); // Inicializace knihovny LCD

	// Nekonecna smycka
	while (1) {
		switch (valve) // Switch, kde se preskakuje po ventilech
		{
		case start: // Defaultni case, kde se ceka na inicializaci programu uzivatelem
			LCD_puts("Press SW1 to start"); // Vypsani textu na LCD
			while (!IsKeyPressed(SWITCH_PIN)); // Pokud je zmacknute tlacitko
			valve = nadrz1; // Zapni misici jednotku, respektive preskoc na osetreni prvniho ventilu
			LCD_clear(); // Vymazani obsahu LCD
			break;
		case nadrz1: // TANK 1 // Case, ktery osetruje prvni ventil
			if (tank1 < CTVRT_NADRZE || tank1 > CELA_NADRZ) // Osetreni validniho vstupu
			{
				valve = nadrz2;
				break;
			}
			PTE->PSOR = PTE->PSOR | (1 << SV1_PIN); // Otevreni ventilu SV1
			if (tank1 == CTVRT_NADRZE) // Pokud byla puvodni hodnota nastavena na 1
			{
				LCD_puts("Filling tank 1->25%"); // Vypsani textu na LCD
				while ((PTD->PDIR & (1 << H3_PIN)) == 0); // Napoustej vodu, dokud nebude ve vysi hladinomeru H3

			} else if (tank1 == PUL_NADRZE) // Pokud byla puvodni hodnota nastavena na 2
			{
				LCD_puts("Filling tank 1->50%"); // Vypsani textu na LCD
				while ((PTC->PDIR & (1 << H2_PIN)) == 0); // Napoustej vodu, dokud nebude ve vysi hladinomeru H2
			} else if (tank1 == CELA_NADRZ) // Pokud byla puvodni hodnota nastavena na 3
			{
				LCD_puts("Filling tank 1->100%"); // Vypsani textu na LCD
				while ((PTD->PDIR & (1 << H1_PIN)) == 0); // Napoustej vodu, dokud nebude ve vysi hladinomeru H1
			}
			PTE->PCOR = PTE->PCOR | (1 << SV1_PIN); // Zavri ventil SV1
			valve = nadrz2; // Preskoc na dalsi ventil
			LCD_clear(); // Vymazani obsahu LCD
			break;
		case nadrz2: // TANK 2 // Case, ktery osetruje druhy ventil
			if (tank2 < CTVRT_NADRZE || tank2 > CELA_NADRZ || tank2 == PUL_NADRZE) // Osetreni validniho vstupu
			{
				valve = nadrz3;
				break;
			}
			PTC->PSOR = PTC->PSOR | (1 << SV2_PIN); // Otevreni ventilu SV2
			if (tank2 == CTVRT_NADRZE) // Pokud byla puvodni hodnota nastavena na 1
			{
				LCD_puts("Filling tank 2->25%"); // Vypsani textu na LCD
				while ((PTD->PDIR & (1 << H5_PIN)) == 0); // Napoustej vodu, dokud nebude ve vysi hladinomeru H5
			} else if (tank2 == CELA_NADRZ) // Pokud byla puvodni hodnota nastavena na 3
			{
				LCD_puts("Filling tank 2->100%"); // Vypsani textu na LCD
				while ((PTC->PDIR & (1 << H4_PIN)) == 0); // Napoustej vodu, dokud nebude ve vysi hladinomeru H4
			}
			PTC->PCOR = PTC->PCOR | (1 << SV2_PIN); // Zavreni ventilu SV2
			valve = nadrz3; // Preskoc na dalsi ventil
			LCD_clear(); // Vymazani obsahu LCD
			break;
		case nadrz3: // TANK 3 // Case, ktery osetruje treti ventil
			if (tank3 < CTVRT_NADRZE || tank3 > CELA_NADRZ) // Osetreni validniho vstupu
			{
				valve = mix;
				break;
			}
			PTE->PSOR = PTE->PSOR | (1 << SV3_PIN); // Otevreni ventilu SV3
			if (tank3 == CTVRT_NADRZE) // Pokud byla puvodni hodnota nastavena na 1
			{
				LCD_puts("Filling tank 3->25%"); // Vypsani textu na LCD
				while ((PTC->PDIR & (1 << H8_PIN)) == 0); // Napoustej vodu, dokud nebude ve vysi hladinomeru H8
			} else if (tank3 == PUL_NADRZE) // Pokud byla puvodni hodnota nastavena na 2
			{
				LCD_puts("Filling tank 3->50%"); // Vypsani textu na LCD
				while ((PTD->PDIR & (1 << H7_PIN)) == 0); // Napoustej vodu, dokud nebude ve vysi hladinomeru H7
			} else if (tank3 == CELA_NADRZ) // Pokud byla puvodni hodnota nastavena na 3
			{
				LCD_puts("Filling tank 3->100%"); // Vypsani textu na LCD
				while ((PTC->PDIR & (1 << H6_PIN)) == 0); // Napoustej vodu, dokud nebude ve vysi hladinomeru H6
			}
			PTE->PCOR = PTC->PCOR | (1 << SV3_PIN); // Zavreni ventilu SV3
			valve = mix; // Preskoc na dalsi ventil
			LCD_clear(); // Vymazani obsahu LCD
			break;
		case mix: // MIX // Case, ktery osetruje ventil pro misici nadrz
			PTE->PSOR = PTE->PSOR | (1 << SV4_PIN); // Otevreni ventilu SV4
			LCD_puts("Filling MIX tank"); // Vypsani textu na LCD
			PTD->PSOR = PTD->PSOR | (1 << MIX_PIN); // Zapnuti miseni
			if (((PTD->PDIR & (1 << H3_PIN)) == 0)
					&& ((PTD->PDIR & (1 << H5_PIN)) == 0)
					&& (PTC->PDIR & (1 << H8_PIN)) == 0) // Pokud jsou vsechny nadrze vyprazdneny
			{
				PTE->PCOR = PTC->PCOR | (1 << SV4_PIN); // Zavreni ventilu SV4
				LCD_clear();
				LCD_puts("Mixing"); // Vypsani textu na LCD
				SYSTICK_delay_ms(5000); // Pockej 5s
				PTD->PCOR = PTD->PCOR | (1 << MIX_PIN); // Vypnuti miseni
				valve = vylevani; // Preskoc na dalsi ventil
			}
			LCD_clear(); // Vymazani obsahu LCD
			break;
		case vylevani: // POURING OUT // Case, ktery osetruje vyliti vody z misici jednotky a zavreni vsech ventilu
			LCD_puts("Pouring out"); // Vypsani textu na LCD
			PTE->PSOR = PTE->PSOR | (1 << SV5_PIN); // Otevreni ventilu SV5
			SYSTICK_delay_ms(5000); // Pockej 5s
			PTE->PCOR = PTE->PCOR | (1 << SV5_PIN); // Zavreni ventilu SV5
		    valve = start; // Vypnuti misici jednotky, respektive prechod do defaultniho stavu
			LCD_clear(); // Vymazani obsahu LCD
			break;
		}
	}
	return 0;
}

// Initialize the pins for the Mix model
void init(void) {
// Enable clock for ports A, B, C, D, E
	SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK |
	SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK);
// Set pin function to GPIO
	PORTA->PCR[SWITCH_PIN] = PORT_PCR_MUX(1);
	PORTA->PCR[SWITCH_PIN_2] = PORT_PCR_MUX(1);

	PORTE->PCR[SV1_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[SV2_PIN] = PORT_PCR_MUX(1);
	PORTE->PCR[SV3_PIN] = PORT_PCR_MUX(1);
	PORTE->PCR[SV4_PIN] = PORT_PCR_MUX(1);
	PORTE->PCR[SV5_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[MIX_PIN] = PORT_PCR_MUX(1);

	PORTD->PCR[H1_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[H2_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[H3_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[H4_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[H5_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[H6_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[H7_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[H8_PIN] = PORT_PCR_MUX(1);

// Set pin direction
	PTE->PDDR |= (1 << SV1_PIN); // SV1 is output - valve 1
	PTC->PDDR |= (1 << SV2_PIN);
	PTE->PDDR |= (1 << SV3_PIN);
	PTE->PDDR |= (1 << SV4_PIN);
	PTE->PDDR |= (1 << SV5_PIN);
	PTD->PDDR |= (1 << MIX_PIN);

// Hx are inputs (sensors)
	PTD->PDDR &= ~(1 << H1_PIN);
	PTC->PDDR &= ~(1 << H2_PIN);
	PTD->PDDR &= ~(1 << H3_PIN);
	PTC->PDDR &= ~(1 << H4_PIN);
	PTD->PDDR &= ~(1 << H5_PIN);
	PTC->PDDR &= ~(1 << H6_PIN);
	PTD->PDDR &= ~(1 << H7_PIN);
	PTC->PDDR &= ~(1 << H8_PIN);
// pull ups are not needed.

}
/* Return 1 if the switch on given pin is pressed, 0 if not pressed.
 * */
static inline int IsKeyPressed(int pin) {
	if ((PTA->PDIR & (1 << pin)) == 0)
		return 1;
	else
		return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
