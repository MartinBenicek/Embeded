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

//Switch_pin 22 = D0
#define MIX_PIN 0
//SV1_PIN 11 = E5
#define SV1_PIN 5
//SV2_PIN 12 = C1
#define SV2_PIN 1
//SV3_PIN 13 = E4
#define SV3_PIN 4
//SV4_PIN 15 = E0
#define SV4_PIN 0
//SV5_PIN 16 = E1
#define SV5_PIN 1
//H1 24 = D3
#define H1_PIN 3
//H2 28 = C16
#define H2_PIN 16
//H3 23 = D2
#define H3_PIN 2
//H4 34 = C5
#define H4_PIN 5
//H5 26 = D4
#define H5_PIN 4
//H6 36 = C7
#define H6_PIN 7
//H7 25 = D5
#define H7_PIN 5
//H8 33 = C6
#define H8_PIN 6
#define		SW1		(4)
#define		SW2		(5)
#define		SW3		(6)
#define		SW4		(7)

static int i = 0;

void delay(void);


typedef enum Stavy_Mixeru{
	start,
	plneni1,
	plneni2,
	plneni3,
	plneniMixeru,
	vypousteni1,
	vyposteni2,
	vypousteni3,
	vypousteniMixeru
} aktualniStav;


int main(void)
{

    /* Write your code here */
	init();
	SYSTICK_initialize();

	aktualniStav stav = start;

	MIXER_NastavVentil(SV1_PIN, 0, 0);
	MIXER_NastavVentil(SV2_PIN, 0, 1);
	MIXER_NastavVentil(SV3_PIN, 0, 0);
	MIXER_NastavVentil(SV4_PIN, 0, 0);
	MIXER_NastavVentil(SV5_PIN, 0, 0);

	int tank1;
	int tank2;
	int tank3;

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    while(1){
/*
    	if(MIXER_SledovatHladinu(H3_PIN, 0) == 0){
    		MIXER_NastavVentil(SV1_PIN, 1, 0);
    		MIXER_NastavVentil(SV4_PIN, 0, 0);
    		MIXER_NastavVentil(SV5_PIN, 0, 0);
    	}

    	if(MIXER_SledovatHladinu(H1_PIN, 0) == 1){
    		MIXER_NastavVentil(SV1_PIN, 0, 0);
    		MIXER_NastavVentil(SV4_PIN, 1, 0);
    		SYSTICK_delay_ms(2000);
    		MIXER_NastavVentil(SV4_PIN, 0, 0);
    		MIXER_NastavMichadlo(1);
    		SYSTICK_delay_ms(3000);
    		MIXER_NastavMichadlo(0);
    		MIXER_NastavVentil(SV5_PIN, 1, 0);
    		SYSTICK_delay_ms(2000);
    	}


		if ( IsKeyPressed(OFF_PIN) )

    	*/
    	/*
    	sw1 støední H2, H5, H7

    	sw2 bílá H3, H4, H8

    	sw3 silná H1, H5, H6
    	*/
    	if ( IsKeyPressed(SW1) ){
			tank1 = H2_PIN;
			tank2 = H5_PIN;
			tank3 = H7_PIN;
    	} else if(IsKeyPressed(SW2)){}





			switch(stav){
				case start:
					MIXER_NastavVentil(SV1_PIN, 0, 0);
					MIXER_NastavVentil(SV2_PIN, 0, 1);
					MIXER_NastavVentil(SV3_PIN, 0, 0);
					stav = plneni1;
					break;
				case plneni1:
				case plneni2:
				case plneni3:
					if(MIXER_SledovatHladinu(tank1, 0) == 1)
					break;
			}

    }
    /* Never leave main */
    return 0;
}

void delay(void)
{
	uint32_t n = 100000;
	while( n -- )
		;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
