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
#include "mixer.h"
#include "drv_systick.h"
#include "drv_gpio.h"
#include "drv_lcd.h"

#define MIX_PIN	0	// Switch_pin 22 = D0	- Spusteni mixeru
#define SV1_PIN	5	// SV1_PIN 11 = E5		- Ventil plneni tanku 1
#define SV2_PIN	1	// SV2_PIN 12 = C1		- Ventil plneni tanku 2
#define SV3_PIN	4	// SV3_PIN 13 = E4		- Ventil plneni tanku 3
#define SV4_PIN	0	// SV4_PIN 15 = E0		- Ventil plneni mixeru
#define SV5_PIN	1	// SV5_PIN 16 = E1		- Ventil vypousteni mixeru

#define H1_PIN 	3	// H1 24 = D3			- Hladinomer 3/3 nadrze (Tank 1)
#define H2_PIN 	16	// H2 28 = C16			- Hladinomer 2/3 nadrze (Tank 1)
#define H3_PIN 	2	// H3 23 = D2			- Hladinomer 1/3 nadrze (Tank 1)
#define H4_PIN 	5	// H4 34 = C5			- Hladinomer 2/2 nadrze (Tank 2)
#define H5_PIN 	4	// H5 26 = D4			- Hladinomer 1/2 nadrze (Tank 2)
#define H6_PIN 	7	// H6 36 = C7			- Hladinomer 3/3 nadrze (Tank 3)
#define H7_PIN 	5	// H7 25 = D5			- Hladinomer 2/3 nadrze (Tank 3)
#define H8_PIN 	6	// H8 33 = C6			- Hladinomer 1/3 nadrze (Tank 3)


// Definice naplneni nadrzi
int tank1;
int tank2;
int tank3;


typedef enum Stavy_Mixeru{
	stav_cekani,
	stav_plneni1, 			// plneni tanku 1
	stav_plneni2, 			// plneni tanku 2
	stav_plneni3, 			// plneni tanku 3
	stav_plneniMixeru,		// plneni mixeru (Vypusteni všech tanku)
	stav_mixovani,			// mixovani
	stav_vypousteniMixeru,	// vypousteni mixeru
	stav_hotovo,			// hotovo
	stav_storno				// ukon?ení programu
} aktualniStav;

// Vychozi stav mixeru
aktualniStav stav = stav_cekani;


// Prototypy funkci
void handleButtons();
void handleMixerState(void);
void updateLCD(void);


int main(void)
{

    /* Write your code here */
	init();
	GPIO_Initialize();
	SYSTICK_initialize();
	LCD_initialize();

	// Nastaveni vychoziho stavu ventilu
	MIXER_NastavVentil(SV1_PIN, 0);
	MIXER_NastavVentil(SV2_PIN, 0);
	MIXER_NastavVentil(SV3_PIN, 0);
	MIXER_NastavVentil(SV4_PIN, 0);
	MIXER_NastavVentil(SV5_PIN, 0);


    /* This for loop should be replaced. By default this loop allows a single stepping. */
    while(1){
		handleButtons();
		updateLCD();
		handleMixerState();
    }
    /* Never leave main */
    return 0;
}

void handleButtons(){

	if ( IsKeyPressed(SW1) && stav == stav_cekani){			// Nastaveni na Stredni kavu
		tank1 = H2_PIN;
		tank2 = H5_PIN;
		tank3 = H7_PIN;
		stav = stav_plneni1;
	} else if(IsKeyPressed(SW2) && stav == stav_cekani){	// Nastaveni na Bílou kavu
		tank1 = H3_PIN;
		tank2 = H4_PIN;
		tank3 = H8_PIN;
		stav = stav_plneni1;
	} else if(IsKeyPressed(SW3) && stav == stav_cekani){	// Nastaveni na Silnou kavu
		tank1 = H1_PIN;
		tank2 = H5_PIN;
		tank3 = H6_PIN;
		stav = stav_plneni1;
	} else if(IsKeyPressed(SW4)){	// Storno
		stav = stav_storno;
	}
}

void handleMixerState(void){
	static int probihaMichani = 0;

	switch (stav) {
		case stav_plneni1:
			MIXER_NastavVentil(SV1_PIN, 1);				// Otevreni ventilu pro plneni tanku 1
			if (MIXER_SledovatHladinu(tank1) == 1) {	// Pokud je hladina na senzoru
				MIXER_NastavVentil(SV1_PIN, 0);			// Zavreni ventilu
				stav = stav_plneni2;					// Prechod do stavu plneni tanku 2
			}
			break;

		case stav_plneni2:
			MIXER_NastavVentil(SV2_PIN, 1);				// Otevreni ventilu pro plneni tanku 2
			if (MIXER_SledovatHladinu(tank2) == 1) {	// Pokud je hladina na senzoru
				MIXER_NastavVentil(SV2_PIN, 0);			// Zavreni ventilu
				stav = stav_plneni3;					// Prechod do stavu plneni tanku 3
			}
			break;

		case stav_plneni3:
			MIXER_NastavVentil(SV3_PIN, 1);				// Otevreni ventilu pro plneni tanku 3
			if (MIXER_SledovatHladinu(tank3) == 1) {	// Pokud je hladina na senzoru
				MIXER_NastavVentil(SV3_PIN, 0);			// Zavreni ventilu
				stav = stav_plneniMixeru;				// Prechod do stavu plneni mixeru
			}
			break;

		case stav_plneniMixeru:
			MIXER_NastavVentil(SV4_PIN, 1);				// Otevreni ventilu pro plneni mixeru
			if (MIXER_SledovatHladinu(H3_PIN) == 0 && 	// Pokud tank 1 je prazdny
				MIXER_SledovatHladinu(H5_PIN) == 0 && 	// Pokud tank 2 je prazdny
				MIXER_SledovatHladinu(H8_PIN) == 0) { 	// Pokud tank 3 je prazdny
				SYSTICK_delay_ms(1000); 				// Cekani 1s 
				MIXER_NastavVentil(SV4_PIN, 0); 		// Zavreni ventilu
				probihaMichani = 0;						// Nastaveni promenne na 0
				stav = stav_mixovani;					// Prechod do stavu mixovani
			}
			break;

		case stav_mixovani:
			MIXER_NastavMichadlo(1);					// Zapnuti michacky
			if(!probihaMichani){						// Pokud michani nebylo spusteno
				SYSTICK_delay_ms(5000);					// Michani po dobu 5s -tohle by se dala menit pomoci potenciometru
				probihaMichani = 1;	
			}
			if (probihaMichani){ 						// Pokud michani probehlo
				MIXER_NastavMichadlo(0);				// Vypnuti michacku
				stav = stav_vypousteniMixeru;			// Prechod do stavu vypousteni mixeru
			}
			break;

		case stav_vypousteniMixeru:
			MIXER_NastavVentil(SV5_PIN, 1);				// Otevreni ventilu pro vypousteni mixeru
			if (MIXER_SledovatHladinu(H4_PIN) == 1) {	// Pokud je hladina na senzoru
				MIXER_NastavVentil(SV5_PIN, 0);			// Zavreni ventilu
				stav = stav_hotovo;						// Prechod do stavu hotovo
			}
			break;

		case stav_hotovo:
			SYSTICK_delay_ms(3000);						// Cekani 3s
			stav = stav_cekani;							// Prechod do stavu cekani
			break;

		case stav_storno:
			MIXER_NastavVentil(SV1_PIN, 0);				// Zavreni vsech ventilu
			MIXER_NastavVentil(SV2_PIN, 0);
			MIXER_NastavVentil(SV3_PIN, 0);
			MIXER_NastavVentil(SV4_PIN, 0);
			MIXER_NastavVentil(SV5_PIN, 0);
			MIXER_NastavMichadlo(0);					// Vypnuti michacky
			SYSTICK_delay_ms(3000);						// Cekani 3s
			stav = stav_cekani;							// Prechod do stavu cekani
			break;
		case stav_cekani:
		default:
			break;
	}
}

/**
 * Funkce pro aktualizaci LCD
 */
void updateLCD(void) {
	LCD_clear();
	switch (stav){
		case stav_plneni1:
			LCD_set_cursor(1,1);
			LCD_puts("Plneni prvniho tanku");
			LCD_set_cursor(2,1);
			LCD_puts("Kavu jste zvolili:");
			LCD_set_cursor(3,1);
			if (tank1 == H1_PIN) {
				LCD_puts("Velkou");
			} else if (tank1 == H2_PIN) {
				LCD_puts("Stredni");
			} else if (tank1 == H3_PIN) {
				LCD_puts("Malou");
			}
			break;

		case stav_plneni2:
			LCD_set_cursor(1,1);
			LCD_puts("Plneni druheho tanku");
			LCD_set_cursor(2,1);
			LCD_puts("Mnozstvi mleka jse zvolili:");
			LCD_set_cursor(3,1);
			if (tank2 == H4_PIN) {
				LCD_puts("Hodne");
			} else if (tank2 == H5_PIN) {
				LCD_puts("Malo");
			}
			break;
		
		case stav_plneni3:
			LCD_set_cursor(1,1);
			LCD_puts("Plneni tretiho tanku");
			LCD_set_cursor(2,1);
			LCD_puts("Mnozstvi cukru jste zvolili:");
			LCD_set_cursor(3,1);
			if (tank3 == H6_PIN) {
				LCD_puts("20g");
			} else if (tank3 == H7_PIN) {
				LCD_puts("10g");
			} else if (tank3 == H8_PIN) {
				LCD_puts("Zadne");
			}
			break;

		case stav_plneniMixeru:
			LCD_set_cursor(1,1);
			LCD_puts("Plnim Mixer");
			break;

		case stav_mixovani:
			LCD_set_cursor(1,1);
			LCD_puts("Micham...");
			break;

		case stav_vypousteniMixeru:
			LCD_set_cursor(1,1);
			LCD_puts("Leju kavu do salku");
			break;

		case stav_hotovo:
			LCD_set_cursor(1,1);
			LCD_puts("Vasa kava je hotova");
			break;

		case stav_storno:
			LCD_set_cursor(1,1);
			LCD_puts("Stornujem...");
			break;

		case stav_cekani:
		default:
			LCD_set_cursor(1,1);
			LCD_puts("Vyberte kavu:");
			LCD_set_cursor(2,1);
			LCD_puts("Stredni  Bila  Silna");
			LCD_set_cursor(3,1);
			LCD_puts("  SW1    SW2   SW3  ");
			LCD_set_cursor(4,1);
			LCD_puts("Storno: SW4");
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
