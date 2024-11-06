/*
 * mixer.h
 *
 *  Created on: 21. 10. 2024
 *      Author: m_benicek, s_bucka
 */

#ifndef SOURCES_MIXER_H_
#define SOURCES_MIXER_H_

//inicializace jednotky
void init(void);
//state nahradit int za bool
void MIXER_NastavVentil(int ventil, int state, int c);

int MIXER_SledovatHladinu(int sensor, int c);

void MIXER_NastavMichadlo(int state);

static inline int IsKeyPressed(int pin);

void MIXER_storno();

#endif /* SOURCES_MIXER_H_ */
