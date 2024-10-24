/*
 * mixer.h
 *
 *  Created on: 23. 10. 2023
 *      Author: student
 */

#ifndef SOURCES_MIXER_H_
#define SOURCES_MIXER_H_

/* Inicializuje mix�r */
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
 * int valve - zvolen� ventil
 *
 * Otev�e zvolen� ventil
 * */
void mixer_valveOpen(int valve);

/* *
 * int valve - zvolen� ventil
 *
 * Zav�e zvolen� ventil
 * */
void mixer_valveClose(int valve);

/* *
 * Zapne mix�r
 * */
void mixer_mixerStart();

/* *
 * Vypne mix�r
 * */
void mixer_mixerStop();

/* *
 * return int - 1 nebo 0
 * int hladina - zvolen� indik�tor hladiny
 *
 * Vrac� 1 pokud zvolen� indik�tor sv�t� jinak 0
 * */
int mixer_isReached(int hladina);

/* *
 * return double - �as
 * int hladina - zvolen� indik�tor hladiny
 *
 * Vrac� �as pot�ebn� k vypu�t�n� n�dr�e p�i napln�n� do zvoln� hladiny
 *
 * */
double mixer_getTimeNeeded(int hladina);

#endif /* SOURCES_MIXER_H_ */
