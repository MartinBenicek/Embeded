/*
 * mixer.h
 *
 *  Created on: 21. 10. 2024
 *      Author: m_benicek
 */

#ifndef SOURCES_MIXER_H_
#define SOURCES_MIXER_H_

//inicializace mísící jednotky
void init(void);

void MIXER_NastavVentil(int ventil, int state);

void MIXER_NastavMichadlo(int state);

void MIXER_SledovatHladinu(int sensor);

#endif /* SOURCES_MIXER_H_ */
