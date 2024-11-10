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

void delay(void);
void ADCInit(void);
uint32_t ADCCalibrate(void);


// Definice tlacitek
#define		SW1		(4)	// Stredn�
#define		SW2		(5)	// B�l�
#define		SW3		(6)	// Siln�	
#define		SW4		(7)	// Storno (Ukonceni programu)

// Definice naplneni nadrzi
int tank1;
int tank2;
int tank3;



typedef enum Stavy_Mixeru{
	stav_cekani,
	stav_plneni1, 			// plneni tanku 1
	stav_plneni2, 			// plneni tanku 2
	stav_plneni3, 			// plneni tanku 3
	stav_plneniMixeru,		// plneni mixeru (Vypusteni v�ech tanku)
	stav_mixovani,			// mixovani
	stav_vypousteniMixeru,	// vypousteni mixeru
	stav_hotovo,			// hotovo
	stav_storno				// ukon?en� programu
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
	SYSTICK_initialize();
	LCD_initialize();
	ADCInit();
	ADCCalibrate();
	ADCInit();
	PORTC->PCR[2] = PORT_PCR_MUX(0);

	

	// Nastaveni vychoziho stavu ventilu
	MIXER_NastavVentil(SV1_PIN, 0);
	MIXER_NastavVentil(SV2_PIN, 0);
	MIXER_NastavVentil(SV3_PIN, 0);
	MIXER_NastavVentil(SV4_PIN, 0);
	MIXER_NastavVentil(SV5_PIN, 0);


    /* This for loop should be replaced. By default this loop allows a single stepping. */
    while(1){
		//po uint16 smazat
		ADC0->SC1[0] = ADC_SC1_ADCH(11);
		while ( (ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0 )
			;
		uint16_t vysledek = ADC0->R[0];
		handleButtons();
		updateLCD(vysledek);
		handleMixerState(vysledek);
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
	} else if(IsKeyPressed(SW2) && stav == stav_cekani){	// Nastaveni na B�lou kavu
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

void handleMixerState(vysledek){
	static int probihaMichani = 0;

	switch (stav) {
		case stav_plneni1:
			MIXER_NastavVentil(SV1_PIN, 1);
			if (MIXER_SledovatHladinu(tank1) == 1) {
				MIXER_NastavVentil(SV1_PIN, 0);
				stav = stav_plneni2;
			}
			break;

		case stav_plneni2:
			MIXER_NastavVentil(SV2_PIN, 1);
			if (MIXER_SledovatHladinu(tank2) == 1) {
				MIXER_NastavVentil(SV2_PIN, 0);
				stav = stav_plneni3;
			}
			break;

		case stav_plneni3:
			MIXER_NastavVentil(SV3_PIN, 1);
			if (MIXER_SledovatHladinu(tank3) == 1) {
				MIXER_NastavVentil(SV3_PIN, 0);
				stav = stav_plneniMixeru;
			}
			break;

		case stav_plneniMixeru:
			MIXER_NastavVentil(SV4_PIN, 1);
			if (MIXER_SledovatHladinu(tank1) == 1 &&
				MIXER_SledovatHladinu(tank2) == 1 && 
				MIXER_SledovatHladinu(tank3) == 1) {
				SYSTICK_delay_ms(1000); // Cekani na stabilizaci hladin
				MIXER_NastavVentil(SV4_PIN, 0); // Zavreni ventilu
				probihaMichani = 0;
				stav = stav_mixovani;
			}
			break;

		case stav_mixovani:
			MIXER_NastavMichadlo(1);
			if(!probihaMichani){
				int delay_ms;
				if(vysledek < 203){
					delay_ms = 2000;
				} else if(vysledek > 203){
					delay_ms = 3000;
				} else if(vysledek > 407){
					delay_ms = 4000;
				} else if(vysledek > 611){
					delay_ms = 5000;
				} else if(vysledek > 815){
					delay_ms = 6000;
				}
				SYSTICK_delay_ms(delay_ms);		// Michani po dobu 5s -tohle by se dala menit pomoci potenciometru
				probihaMichani = 1;	
			}
			if (probihaMichani){ 			// Pokud michani probehlo
				MIXER_NastavMichadlo(0);	// Vypnuti michacku
				stav = stav_vypousteniMixeru;
			}
			break;

		case stav_vypousteniMixeru:
			MIXER_NastavVentil(SV5_PIN, 1);
			if (MIXER_SledovatHladinu(H4_PIN) == 1) {
				MIXER_NastavVentil(SV5_PIN, 0);
				stav = stav_hotovo;
			}
			break;

		case stav_hotovo:
			SYSTICK_delay_ms(3000);
			stav = stav_cekani;
			break;

		case stav_storno:
			MIXER_NastavVentil(SV1_PIN, 0);
			MIXER_NastavVentil(SV2_PIN, 0);
			MIXER_NastavVentil(SV3_PIN, 0);
			MIXER_NastavVentil(SV4_PIN, 0);
			MIXER_NastavVentil(SV5_PIN, 0);
			MIXER_NastavMichadlo(0);
			SYSTICK_delay_ms(3000);
			stav = stav_cekani;
			break;
		case stav_cekani:
		default:
			break;
	}
}

void updateLCD(vysledek) {
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
			int delay_ms;
			if(vysledek < 203){
				delay_ms = 2000;
			} else if(vysledek > 203){
				delay_ms = 3000;
			} else if(vysledek > 407){
				delay_ms = 4000;
			} else if(vysledek > 611){
				delay_ms = 5000;
			} else if(vysledek > 815){
				delay_ms = 6000;
			}
			delay_ms /= 1000;
			LCD_set_cursor(1,1);
			LCD_puts("Stredni  Bila  Silna");
			LCD_set_cursor(2,1);
			LCD_puts("  SW1    SW2   SW3  ");
			LCD_set_cursor(3,1);
			LCD_puts("Storno: SW4");
			LCD_set_cursor(4,1);
			LCD_puts("Doba michani: ");
			LCD_set_cursor(4,15);
			LCD_puts(delay_ms);
			LCD_set_cursor(4,16);
			LCD_puts("s");
			break;
	}
}

void ADCInit(void)
{
	// Povolit hodinovy signal pro ADC
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	// Zakazeme preruseni, nastavime kanal 31 = A/D prevodnik vypnut, jinak by zapisem
	// doslo ke spusteni prevodu
	// Vybereme single-ended mode
	ADC0->SC1[0] =  ADC_SC1_ADCH(31);

	// Vyber hodinoveho signalu, preddelicky a rozliseni
	// Clock pro ADC nastavime <= 4 MHz, coz je doporuceno pro kalibraci.
	// Pri max. CPU frekvenci 48 MHz je bus clock 24 MHz, pri delicce = 8
	// bude clock pro ADC 3 MHz
	ADC0->CFG1 = ADC_CFG1_ADICLK(0)		/* ADICLK = 0 -> bus clock */
		| ADC_CFG1_ADIV(3)				/* ADIV = 3 -> clock/8 */
		| ADC_CFG1_MODE(2);				/* MODE = 2 -> rozliseni 10-bit */

	// Do ostatnich registru zapiseme vychozi hodnoty:
	// Vybereme sadu kanalu "a", vychozi nejdelsi cas prevodu (24 clocks)
	ADC0->CFG2 = 0;

	// Softwarove spousteni prevodu, vychozi reference
	ADC0->SC2 = 0;

	// Hardwarove prumerovani vypnuto
	ADC0->SC3 = 0;	/* default values, no averaging */

}

uint32_t ADCCalibrate(void)
{
	 unsigned short cal_var;

	  ADC0->SC2 &= ~ADC_SC2_ADTRG_MASK;	/* Enable Software Conversion Trigger for Calibration Process */
	  ADC0->SC3 &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK );    /* set single conversion, clear avgs bitfield for next writing */

	  ADC0->SC3 |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(32) ); /* turn averaging ON and set desired value */

	  ADC0->SC3 |= ADC_SC3_CAL_MASK;      /* Start CAL */

	  /* Wait calibration end */
	  while ( (ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0 )
		  ;

	  /* Check for Calibration fail error and return */
	  if ( (ADC0->SC3 & ADC_SC3_CALF_MASK) != 0 )
		  return 1;

	  // Calculate plus-side calibration
	  cal_var = 0;
	  cal_var =  ADC0->CLP0;
	  cal_var += ADC0->CLP1;
	  cal_var += ADC0->CLP2;
	  cal_var += ADC0->CLP3;
	  cal_var += ADC0->CLP4;
	  cal_var += ADC0->CLPS;

	  cal_var = cal_var/2;
	  cal_var |= 0x8000; // Set MSB
	  ADC0->PG = ADC_PG_PG(cal_var);

	  // Calculate minus-side calibration
	  cal_var = 0;
	  cal_var =  ADC0->CLM0;
	  cal_var += ADC0->CLM1;
	  cal_var += ADC0->CLM2;
	  cal_var += ADC0->CLM3;
	  cal_var += ADC0->CLM4;
	  cal_var += ADC0->CLMS;

	  cal_var = cal_var/2;
	  cal_var |= 0x8000; // Set MSB
	  ADC0->MG = ADC_MG_MG(cal_var);

	  ADC0->SC3 &= ~ADC_SC3_CAL_MASK;

	  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
