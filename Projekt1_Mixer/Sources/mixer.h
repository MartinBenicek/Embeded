/*
 * mixer.h
 *
 *  Created on: 23. 10. 2023
 *      Author: student
 */

#ifndef SOURCES_MIXER_H_
#define SOURCES_MIXER_H_

/* Inicializuje mixér */
void mixer_init(void);

typedef enum _mixer_valves {
	MIXER,
	SV1,
	SV2,
	SV3,
	SV4,
	SV5,

};

typedef enum _mixer_indicators {
	H1,
	H2,
	H3,
	H4,
	H5,
	H6,
	H7,
	H8,
};



/* *
 * int valve - zvolený ventil
 *
 * Otevøe zvolený ventil
 * */
void mixer_valveOpen(int valve);

/* *
 * int valve - zvolený ventil
 *
 * Zavøe zvolený ventil
 * */
void mixer_valveClose(int valve);

/* *
 * Zapne mixér
 * */
void mixer_mixerStart();

/* *
 * Vypne mixér
 * */
void mixer_mixerStop();

/* *
 * return int - 1 nebo 0
 * int hladina - zvolený indikátor hladiny
 *
 * Vrací 1 pokud zvolený indikátor svítí jinak 0
 * */
int mixer_isReached(int hladina);

/* *
 * return double - èas
 * int hladina - zvolený indikátor hladiny
 *
 * Vrací èas potøebný k vypuštìní nádrže pøi naplnìní do zvolné hladiny
 *
 * */
double mixer_getTimeNeeded(int hladina);

#endif /* SOURCES_MIXER_H_ */
