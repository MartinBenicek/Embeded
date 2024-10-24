#include  <stdbool.h>
// mus� b�t
#ifndef SOURCES_DRV_PRACKA_H_
#define SOURCES_DRV_PRACKA_H_

//definice ��sel vstup� teploty
#define teplota_30 (0)
#define teplota_40 (1)
#define teplota_60 (2)
#define teplota_90 (3)

//definice �rovn� hladiny
#define hladina_pod50 (0)
#define hladina_50 (1)
#define hladina_100 (2)

//Definovani sm�ru bubnu
#define buben_vlevo (0)
#define buben_vpravo (1)
#define buben_stop (2)

//Definovani �as� funkc� pra�ky
#define cas_napoustet_50 (12000)
#define cas_napoustet_100 (24000)
#define	cas_teplota_30 (15000)
#define cas_teplota_40 (20000)
#define cas_teplota_60 (30000)
#define cas_teplota_90 (55000)
#define cas_oplachovani (55000)
#define cas_pumpovani (18000)
#define BUTTON_DELAY (500)
#define LCD_REFRESH_FREQUENCY (300)
#define PROGRESS_SPINNER_REFRESH_FREQUENCY (300)
#define cas_umyvani (10000)
#define cas_suseni (20000)
#define pumpovani_delay (15000)

//Definice prom�n�ch
static int i = 0;
static int vyber_teplota = teplota_30;
static bool omyvat = false;
static uint32_t napousteni_casovac;
static uint32_t topeni_casovac;
static int vyber_teplota_cas;

//Definice pro case
static enum {
	START,
	NAPOUSTENI,
	TOPENI,
	MYTI,
	CERPANI,
	OPLACHOVANI,
	SUSENI,
	ZASTAVENI
} stav = START;

//DEFINICE N�ZV� FUNKC�
void pracka_inicializace(void);

//1 nebo 0 spust� nebo zastav� napou�t�n�
void pracka_nastavNapousteni(bool hodnota);

//1 nebo 0 spust� nebo zastav� topen�
void pracka_nastavTopeni(bool hodnota);

//2 vstupy do funkce 1. strana to�en� bubnu a rychlost
void pracka_nastavBuben(int strana, bool rychlost);

//zapnut� nebo vypnut� �erpadla
void pracka_nastavCerpadlo(bool hodnota);

//vrac� aktu�ln� hodnotu teploty
int pracka_ctiTeplotu(void);

//vrac� aktu�ln� hladinu vody
int pracka_ctiHladinu(void);

//vrac� analogouvou hodnotu
int AnalogRead(int channel);

//inicializace pra�ky
void pracka_int(void);

//start pra�ky
void pracka_start(void);

//funkce pro napu�t�n� do ur�it� hladiny
int pracka_napousteni(int water_level);

//funkce top� na ur�itou teplotu
int pracka_topeni(int heating_level);

//atomick� funkce pra�ky
void pracka_myti(void);
void pracka_cerpani(void);
void pracka_suseni(void);
void pracka_oplachovani(void);

//yobrayov�n� na displaji
void pracka_displej(const char* stateName);
//p�ejmenovan� su�en� na �d�man�




#endif /* SOURCES_DRV_PRACKA_H_ */
