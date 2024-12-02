/*
 * drv_mixer.h
 *
 *  Created on: 1. 11. 2024
 *      Author: student
 */

#ifndef SOURCES_DRV_MIXER_H_
#define SOURCES_DRV_MIXER_H_

/** Available pins
 * Hodnoty prvku jsou cisla pinu. Port neni resen, ten musi byt "hard-coded" ve funkcich.
 * */
typedef enum _mixer_pins
{
	SV2,
	mix,
	SV4,
	SV5,
	SV3,
	SV1,
	H4,
	H8,
	H6,
	H2,
	H3,
	H1,
	H5,
	H7,
} MIXER_pin;

/** Mozne hodnoty zapisovane na pin */
#define	HIGH	(1)	/* log. 1 */
#define LOW		(0) /* log. 0 */


void MIXER_Init(void);
void mixerVystup(MIXER_pin,uint8_t);
uint8_t hladinaRead(MIXER_pin);

#endif /* SOURCES_DRV_MIXER_H_ */
