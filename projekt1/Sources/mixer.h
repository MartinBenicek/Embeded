/*
 * mixer.h
 *
 *  Created on: 21. 10. 2024
 *      Author: m_benicek, s_bucka
 */

#ifndef SOURCES_MIXER_H_
#define SOURCES_MIXER_H_

// inicializace jednotky
void init(void);

/**
 * Nastaví ventil na daném pinu
 * @param valve_pin pin ventilu
 * @param state     stav ventilu
 *                  - 0 - zavřeno
 *                  - 1 - otevřeno
 */
void MIXER_NastavVentil(uint8_t valve_pin, uint8_t state);

/**
 * Sleduje hladinu na senzoru
 * @param sensor_pin pin senzoru
 * @return  1 - hladina je na senzoru
 *          0 - hladina není na senzoru
 */
uint8_t MIXER_SledovatHladinu(uint8_t sensor_pin);

/**
 * Nastaví míchadlo
 * @param state stav míchadla
 *              - 0 - vypnuto
 *              - 1 - zapnuto
 */
void MIXER_NastavMichadlo(uint8_t state);

/**
 * Kontrola stisknutí tlačítka
 * @param pin pin tlačítka
 * @return  1 - tlačítko je stisknuto
 *          0 - tlačítko není stisknuto
 */
static inline int IsKeyPressed(uint8_t pin);


#endif /* SOURCES_MIXER_H_ */

//  ( ͡° ͜ʖ ͡°) 