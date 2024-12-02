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
#include "drv_gpio.h"
#include "drv_lcd.h"
#include "drv_mixer.h"
#include "drv_systick.h"

typedef enum _mixer_stavy{
	START,
	PLNENI_TANK1,
	PLNENI_TANK2,
	PLNENI_TANK3,
	PLNENI_mixer,
	VYPOUSTENI_TANK1,
	VYPOUSTENI_TANK2,
	VYPOUSTENI_TANK3,
	VYPOUSTENI_mixer,
} MIXER_stavy;

int main(void)
{

	GPIO_Initialize();
	SYSTICK_initialize();
	LCD_initialize();
	MIXER_Init();

	MIXER_stavy stav = START;

    /* Write your code here */
    while (1){

    	switch (stav){

			case START:
				mixerVystup(SV4,LOW);
				stav = PLNENI_TANK1;
				break;
			case PLNENI_TANK1:
				mixerVystup(SV1,HIGH);
				if (hladinaRead(H2)){
					stav = VYPOUSTENI_TANK1;
				}
				break;
			case VYPOUSTENI_TANK1:
				mixerVystup(SV1,LOW);
				mixerVystup(SV4,HIGH);
				mixerVystup(SV5,HIGH);
				if (!hladinaRead(H3)){
					stav = START;
				}

    	}

    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
