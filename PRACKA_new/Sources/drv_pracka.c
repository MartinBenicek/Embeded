
#include "MKL25Z4.h"
#include "drv_pracka.h"
#include <stdbool.h>

//èísla pinù na registrech PORTx VÝSTUPY
#define Pin_buben_vlevo (1)
#define Pin_cerpadlo (0)
#define Pin_voda (0)
#define Pin_topeni (1)
#define Pin_otacky (4)
#define Pin_buben_vpravo (5)

//Èísla pinù pro teplotu a hladinu vody  VSTUPY
#define Pin_teplota_90 (5)
#define Pin_teplota_60 (2)
#define Pin_teplota_40 (16)
#define Pin_teplota_30 (3)
#define Pin_hladina_100 (4)
#define Pin_hladina_50 (6)


//inicializaèní funkce praèky
void pracka_inicializace(void){
	// Povolení hodinového signálu pro port
	SIM->SCGC5 |= (SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK);

	// Nastavení mux na alternativní funkci 1 - GPIO funkce
	PORTC->PCR[Pin_buben_vlevo] = PORT_PCR_MUX(1);
	PORTD->PCR[Pin_cerpadlo] = PORT_PCR_MUX(1);
	PORTE->PCR[Pin_voda] = PORT_PCR_MUX(1);
	PORTE->PCR[Pin_topeni] = PORT_PCR_MUX(1);
	PORTE->PCR[Pin_otacky] = PORT_PCR_MUX(1);
	PORTE->PCR[Pin_buben_vpravo] = PORT_PCR_MUX(1);

	PORTC->PCR[Pin_teplota_90] = PORT_PCR_MUX(1);
	PORTD->PCR[Pin_teplota_60] = PORT_PCR_MUX(1);
	PORTC->PCR[Pin_teplota_40] = PORT_PCR_MUX(1);
	PORTD->PCR[Pin_teplota_30] = PORT_PCR_MUX(1);
	PORTD->PCR[Pin_hladina_100] = PORT_PCR_MUX(1);
	PORTC->PCR[Pin_hladina_50] = PORT_PCR_MUX(1);

	// Nastavení vystupniho rezimu
	GPIOC->PDDR |= (1 << Pin_buben_vlevo);
	GPIOD->PDDR |= (1 << Pin_cerpadlo);
	GPIOE->PDDR |= (1 << Pin_voda);
	GPIOE->PDDR |= (1 << Pin_topeni);
	GPIOE->PDDR |= (1 << Pin_otacky);
	GPIOE->PDDR |= (1 << Pin_buben_vpravo);

	// Nastaveni vstupniho rezimu
	GPIOC->PDDR &= ~(1 << Pin_teplota_90);
	GPIOD->PDDR &= ~(1 << Pin_teplota_60);
	GPIOC->PDDR &= ~(1 << Pin_teplota_40);
	GPIOD->PDDR &= ~(1 << Pin_teplota_30);
	GPIOD->PDDR &= ~(1 << Pin_hladina_100);
	GPIOC->PDDR &= ~(1 << Pin_hladina_50);

	//Nastavení do 0
	GPIOC->PCOR |= (1 << Pin_buben_vlevo);
	GPIOD->PCOR |= (1 << Pin_cerpadlo);
	GPIOE->PCOR |= (1 << Pin_voda);
	GPIOE->PCOR |= (1 << Pin_topeni);
	GPIOE->PCOR |= (1 << Pin_otacky);
	GPIOE->PCOR |= (1 << Pin_buben_vpravo);
}
//	FUNKCE aka DRIVERY

//napouštìní VODY

void pracka_nastavNapousteni(bool hodnota){
	if (hodnota){
		GPIOE->PSOR |= (1<< Pin_voda);
	}else{
		GPIOE->PCOR |= (1<< Pin_voda);
	}
}

//Nastavení smìru a rychlost otáèek bubnu
void pracka_nastavBuben(int strana, bool rychlost){
	if (rychlost){
		GPIOE->PSOR |= (1<< Pin_otacky);
	}else{
		GPIOE->PCOR |= (1<< Pin_otacky);
	}
	//Smìr otáèní

	if (strana == buben_vlevo){
		GPIOE->PCOR |= (1 << Pin_buben_vpravo);
		GPIOC->PSOR |= (1 << Pin_buben_vlevo);

	} else if (strana == buben_vpravo){
		GPIOC->PCOR |= (1 << Pin_buben_vlevo);
		GPIOE->PSOR |= (1 << Pin_buben_vpravo);

	} else if (strana == buben_stop){
		GPIOE->PCOR |= (1 << Pin_buben_vpravo);
		GPIOC->PCOR |= (1 << Pin_buben_vlevo);
	}
}

//Spínaní topení
//void pracka_nastavTopení(bool hodnota){
void pracka_nastavTopeni(bool hodnota){
	if (hodnota){
		GPIOE->PSOR |= (1 << Pin_topeni);
	} else {
		GPIOE->PCOR |= (1 << Pin_topeni);
	}
}

void pracka_nastavCerpadlo(bool hodnota){
	if (hodnota){
		GPIOD->PSOR |= (1 << Pin_cerpadlo);
	} else {
		GPIOD->PCOR |= (1 << Pin_cerpadlo);
	}
}

//ètení teploty (vrací hodnotu jaká je aktuální teplota)
int pracka_ctiTeplotu(void){
	if ((PTC->PDIR & (1 << (uint8_t)Pin_teplota_90)) != 0){
		return teplota_90;
	} else if ((PTD->PDIR & (1 << (uint8_t)Pin_teplota_60)) != 0){
		return teplota_60 ;
	} else if ((PTC->PDIR & (1 << (uint8_t)Pin_teplota_40)) != 0){
		return teplota_40 ;
	} else if ((PTD->PDIR & (1 << (uint8_t)Pin_teplota_30)) != 0){
		return teplota_30 ;
	}

	return -1;
}


//vrací stav hladinz v praèce
int pracka_ctiHladinu(void){
	if ((PTD->PDIR & (1 << (uint8_t)Pin_hladina_100)) != 0){
		return hladina_100 ;
	} else if ((PTC->PDIR & (1 << (uint8_t)Pin_hladina_50)) != 0){
		return hladina_50 ;
	}
	else{
		return hladina_pod50 ;
	}

	return -1;
}
//když chci returnovat hodnoty z funkce, musím použít datový typ funkce INT a vstupní hodnotu void
//PDIR funkce registrù vrací
