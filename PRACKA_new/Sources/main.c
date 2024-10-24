
#include "MKL25Z4.h"
#include "drv_gpio.h"
#include "drv_lcd.h"
#include "drv_systick.h"
#include <stdio.h>
#include <stdbool.h>
#include "drv_pracka.h"

int main(void)
{

	GPIO_Initialize();				//Inicializace knihoven
	LCD_initialize();
	SYSTICK_initialize();
	pracka_inicializace();
	pracka_int();

	while(1)
	{
		if (stav != ZASTAVENI && stav != START){			//Uvolneni tlacitka 4 (STOP), kdyz se pere
			if (pinRead(SW4) == LOW){
				stav = ZASTAVENI;
			}
		}

	static int topeni_krok = 0;


	if (vyber_teplota == teplota_30)						//Podle vybrane teploty z potenciometru zapise do promenne vyber_teplota_cas delku casu k dosazeni teploty
		vyber_teplota_cas = cas_teplota_30;					//Cas je ulozen jako #define v .h
	else if (vyber_teplota == teplota_40)
		vyber_teplota_cas = cas_teplota_40;
	else if (vyber_teplota == teplota_60)
		vyber_teplota_cas = cas_teplota_60;
	else if (vyber_teplota == teplota_90)
		vyber_teplota_cas = cas_teplota_90;

	switch (stav){											//Hlavni switch pro jednotlive stavy pracky

		case START:
					pracka_start();									//Funkce pracka_start() pro zadavani parametru myciho programu
				break;

		case NAPOUSTENI:
					pracka_displej("NAPOUSTENI");					// Funkce napise na displej "napousteni"
					if (pracka_napousteni(hladina_100) == true){			//pokud vrati funkce 1 (dosazena hladina 100), tak se posune na stav topeni
						stav = TOPENI;
					}
			break;

		case TOPENI:
					pracka_displej("TOPENI");						//Stejne jako napousteni
					if (pracka_topeni(vyber_teplota) == true){
						stav = MYTI;
					}
			break;

		case MYTI:
					pracka_myti();
			break;

		case CERPANI:
					pracka_cerpani();
			break;

		case OPLACHOVANI:
					pracka_oplachovani();
			break;

		case SUSENI:
					pracka_suseni();
			break;
///////////////////////////////////////////////////////////////////
		case ZASTAVENI:                                              //Ukonceni prani

					pracka_nastavBuben(buben_stop, false);
					pracka_nastavTopeni(false);
					pracka_nastavNapousteni(false);

					static enum {
						NAPUST,
						CEKEJ
					}
					state = NAPUST;
					static uint32_t startTime;

					pracka_displej("KONEC");

					if (state == NAPUST){
						//pracka_nastavNapousteni(true);
						pracka_nastavCerpadlo(true);
						if (pracka_ctiHladinu() == hladina_pod50){
							startTime = SYSTICK_millis();
							state = CEKEJ;
						}
					} else if (CEKEJ){
						if (SYSTICK_millis() - startTime > pumpovani_delay ){
							//pracka_nastavNapousteni(false);
							pracka_nastavCerpadlo(false);
							stav = START;
						}
					}
			break;
	}
}
return 0;
}
///////////////////////////////////////////////////////////////////

void pracka_start(){                                                              //Výchozí nastavení
	static enum {
		LCDREFRESH,
		LCDSTOP
	} lcd_state = LCDREFRESH;

	static uint32_t lcd_StartTime;
	static uint32_t button_StartTime;

	if (pinRead(SW2) == LOW && SYSTICK_millis() - button_StartTime >= BUTTON_DELAY){
		button_StartTime = SYSTICK_millis();
		omyvat = !omyvat;
	}

	if (lcd_state == LCDREFRESH){
		lcd_StartTime = SYSTICK_millis();
		lcd_state = LCDSTOP;

		LCD_clear();

		LCD_set_cursor(1,1);
		LCD_puts("!!PRACKA!!");

		LCD_set_cursor(2,1);
		LCD_puts("TEPLOTA: ");

		int vstup_tep = AnalogRead(11);

		if (vstup_tep >= 768){
			vyber_teplota = teplota_90;
			LCD_puts("90 C");
		}
		else if (vstup_tep >= 512){
			vyber_teplota = teplota_60;
			LCD_puts("60 C");
		}
		else if (vstup_tep >= 256){
			vyber_teplota = teplota_40;
			LCD_puts("40 C");
		}
		else{
			vyber_teplota = teplota_30;
			LCD_puts("30 C");
		}

		LCD_set_cursor(3,1);

		if (omyvat == true){
			LCD_puts("OPLACH: ON");
		} else {
			LCD_puts("OPLACH: OFF");
		}

		LCD_set_cursor(4,1);
		LCD_puts("SW1= START");

	} else if (lcd_state == LCDSTOP && SYSTICK_millis() - lcd_StartTime >= LCD_REFRESH_FREQUENCY){
		lcd_state = LCDREFRESH;
	}

	if (pinRead(SW1) == LOW){
		stav = NAPOUSTENI;
	}
}
//Funkce napousteni
int pracka_napousteni(int hladina){
	pracka_nastavNapousteni(true);					    //Zapne napoustení

	if (pracka_ctiHladinu() == hladina){				//Cteni hladiny (vraci retezec), pokud se rovna nastavene hladine
		pracka_nastavNapousteni(false);					//vypne napoustení
		return true;
	}

	return false;
}
//Funkce topení
int pracka_topeni(int heating_level){

	pracka_nastavTopeni(true);							//Stejne jako napousteni
	if (pracka_ctiTeplotu() == heating_level){
		pracka_nastavTopeni(false);
		return true;
	}

	return false;
}

//Funkce myti
void pracka_myti(){
	static enum {										//Vyctovy typ pro jednotlive faze myti
		FAZE1,
		FAZE2,
		FAZE3,
		FAZE4
	} state = FAZE1;

	static uint32_t startTime;

	pracka_displej("MYTI");

	 if (state == FAZE1){                                //Faze prani
		startTime = SYSTICK_millis();
		state = FAZE2;
	 } else if (state == FAZE2){
		 pracka_nastavBuben(buben_vlevo, false);

		if (SYSTICK_millis() - startTime > cas_umyvani){
			startTime = SYSTICK_millis();
			state = FAZE3;
		}
	} else if (state == FAZE3){
		pracka_nastavBuben(buben_vpravo, false);

		if (SYSTICK_millis() - startTime > cas_umyvani){
			startTime = SYSTICK_millis();
			state = FAZE4;
		}
	} //else if (state == FAZE4){
	 if (state == FAZE4){
		pracka_nastavBuben(buben_vlevo, false);

		if (SYSTICK_millis() - startTime > cas_umyvani){
			pracka_nastavBuben(buben_stop, false);
			stav = CERPANI;
			//////////
			state = FAZE1;
		}
	}
}
//Funkce napousteni vody
void pracka_cerpani(){
	static enum {
		ST_PUMP,
		ST_WAIT
	} state = ST_PUMP;

	static uint32_t startTime;
	pracka_displej("VYPOUSTENI");

	if (state == ST_PUMP){

		//pracka_nastavNapousteni(true);
		pracka_nastavCerpadlo(true);
		if (pracka_ctiHladinu() == hladina_pod50){
			startTime = SYSTICK_millis();
			state = ST_WAIT;
		}
	} else if (ST_WAIT){
		if (SYSTICK_millis() - startTime > pumpovani_delay ){
			//pracka_nastavNapousteni(false);
			pracka_nastavCerpadlo(false);
			if (omyvat == true){
				stav = OPLACHOVANI;
			} else {
				stav = SUSENI;
			}
		}
	}
}
void pracka_suseni(){                                            //Funkce pro zdimani
	static enum {
		ST_START,
		ST_DRY
	} state = ST_START;

	static uint32_t startTime;
	pracka_displej("ZDIMANI");

	if (state == ST_START){
		startTime = SYSTICK_millis();
		state = ST_DRY;
	} else if (state == ST_DRY){
		if (SYSTICK_millis() - startTime >= cas_suseni){
			pracka_nastavBuben(buben_stop, false);
			stav = START;
		} else {
			pracka_nastavBuben(buben_vpravo, true);
		}
	}
}

void pracka_oplachovani(){                                         //Funkce Oplach
	static enum {
		ST_RINSING_WATERING,
		ST_RINSING_HEATING,
		ST_RINSING_WASHING_1,
		ST_RINSING_WASHING_2,
		ST_RINSING_PUMPING,
		ST_RINSING_PUMPING_WAIT,
	} state = ST_RINSING_WATERING;

	static uint32_t startTime;


	pracka_displej("OPLACH");

	if (state == ST_RINSING_WATERING){
		if (pracka_napousteni(hladina_50) == true){
			state = ST_RINSING_HEATING;
		}
	} else if (state == ST_RINSING_HEATING){
		if (pracka_topeni(teplota_30) == true){
			startTime = SYSTICK_millis();
			state = ST_RINSING_WASHING_1;
		}
	} else if (state == ST_RINSING_WASHING_1){
		pracka_nastavBuben(buben_vlevo, false);

		if (SYSTICK_millis() - startTime > cas_umyvani){
			startTime = SYSTICK_millis();
			state = ST_RINSING_WASHING_2;
		}
	} else if (state == ST_RINSING_WASHING_2){
		pracka_nastavBuben(buben_vlevo, false);

		if (SYSTICK_millis() - startTime > cas_umyvani){
			pracka_nastavBuben(buben_stop, false);
			state = ST_RINSING_PUMPING;
		}
	} else if (state == ST_RINSING_PUMPING){
		//pracka_nastavNapousteni(true);
		pracka_nastavCerpadlo(true);
		if (pracka_ctiHladinu() == hladina_pod50){
			startTime = SYSTICK_millis();
			state = ST_RINSING_PUMPING_WAIT;
		}
	} else if (state == ST_RINSING_PUMPING_WAIT){
		if (SYSTICK_millis() - startTime > pumpovani_delay ){
			//pracka_nastavNapousteni(false);
			pracka_nastavCerpadlo(false);
			stav = SUSENI;
		}
	}
}


void pracka_displej(const char* krok){                          // Funkce pro zobrazovani na display
	static enum {
		LCDREFRESH,
		LCDSTOP
	} lcd_state = LCDREFRESH;

	static uint32_t lcd_StartTime;

	if (lcd_state == LCDREFRESH){
		lcd_StartTime = SYSTICK_millis();
		lcd_state = LCDSTOP;
		LCD_clear();
		LCD_set_cursor(1,1);
		LCD_puts(krok);
		LCD_set_cursor(1,20);
		LCD_set_cursor(3,1);
		LCD_puts("SW4= STOP PRANI");
	} else if (lcd_state == LCDSTOP && SYSTICK_millis() - lcd_StartTime >= LCD_REFRESH_FREQUENCY){
		lcd_state = LCDREFRESH;
	}
}

int AnalogRead(int channel) {                                 //Funkce pro analogový vstup
	ADC0->SC1[0] = ADC_SC1_ADCH(channel);

	// Cekame na dokonceni prevodu
	while ( (ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0 )
	;

	// Ulozime vysledek prevodu
	return ADC0->R[0];
}

/*	ADCInit
    Inicializuje A/D prevodnik
    Nastavuje zdroj hodin na bus clock a delicku na 8,
    rozliseni na 10 bit, ...
*/
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

//	pinMode(SW4, INPUT_PULLUP);
}

/*
  ADCCalibrate
  Kalibrace ADC.
  Kod prevzat z ukazkoveho kodu pro FRDM-KL25Z.
  Pri chybe kalibrace vraci 1, pri uspechu vraci 0
*/
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

void pracka_int(){                                         //Inicializace modelu
	pinMode(SW1, INPUT_PULLUP);
	pinMode(SW2, INPUT_PULLUP);
	pinMode(SW4, INPUT_PULLUP);

	LCD_clear();
	omyvat = false;

	// Inicializace A/D prevodniku
	ADCInit();

	// Kalibrace a nova inicializace
	// Pro dosazeni udavane presnosti musi byt prevodnik kalibrovan po
	// kazdem resetu.
	// Nova inicializace je potreba protoze pri kalibraci
	// je prevodnik prenastaven.
	ADCCalibrate();
	ADCInit();
}

