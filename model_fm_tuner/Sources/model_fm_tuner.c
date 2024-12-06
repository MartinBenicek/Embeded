/*
 Ukazka prace s modulem FM radioprijimac

 Vyuziva ovladac I2C dle CMSIS

 * Postup vytvoreni projektu s ovladacem I2C:
 * 1) Pridat do projektu soubor RTE_Devices.h z CMSIS_Driver/Config.
 * Vhodne je zkopirovat (Copy file) do projektu a ne linkovat (Link to file),
 * aby mohl mit kazdy projekt svou konfiguraci ovladacu.
 *
 * 2) vlozit do zdrojoveho kodu #include "RTE_Device.h"
 *
 * 3) Pridat do projektu zdrojove kody ovladace (ovladacu).
 * I2C: I2C_MKL25Z4.c
 *
 * 4) Pridat slozku KSDK do projektu, pretazenim z Pruzkumnika na projekt
 * a volbou "Link to files and folders". Vznikne tak slozka "KSDK" v projektu.
 *
 * 4) Pridat cesty k nasledujicim umistenim do nastaveni C Compiler Includes:
 *  CMSIS_Driver
 *  KSDK/hal
 *  KSDK/mkl25z4
 *  Muzeme pridat absolutni cesty. Pro cesty v KSDK muzeme take pridat odkazy
 *  pres tlacitko Workspace.
 *  Priklad konkretnich cest v seznamu Includes:
 *  "../../../CMSIS_Driver"
 *  "${workspace_loc:/${ProjName}/KSDK/hal}"
 *  "${workspace_loc:/${ProjName}/KSDK/mkl25z4}"
 *

 */

#include "MKL25Z4.h"
#include "drv_lcd.h"
#include "drv_gpio.h"
#include "RTE_Device.h"
#include "FreeRTOS.h"
#include "semphr.h"

// Adresa obvodu fm tuneru TEA 5767 na sbernici I2C1
// Frekvence max. 400 kHz coz odpovida HIGH_SPEED dle I2C CMSIS
#define	I2C_ADR_FM_TUNER		(0x60)	// Adresa je 0x60
// Kod pro HC08 pouziva 0xC0 protoze adresa je v odesilanem bajtu posunuta vlevo,
// vyuziva se jen 7 bitu pro adresu, 8. bit je RW.

/*************************************************************/
//			FreeRTOS
SemaphoreHandle_t G_Mutex = NULL;				// Semafor pouzity pro synchronizaci


/*************************************************************/
//			Funkce
uint32_t read_freq(void);						// Cteni frekvence z tuneru
void write_freq(uint32_t freq);					// Zapis frekvence do tuneru
void i2c_event(uint32_t event) { }				// Obsluha udalosti I2C	
void intToStr(int N, char *str);				// Prevod integeru na retezec
void delay(void);								// Zpozdeni
void switch_init(void);							// Inicializace tlacitek
int switch_readw(int SW);						// Cteni stavu tlacitek
void TaskPrint(void * pvParameters);			// Task pro vypis na LCD
void TaskReadButtons (void* pvParameters);		// Task pro cteni tlacitek

/*************************************************************/
//			Definice
#define SWITCH_PRESSED  	(1)					// Stisknuto
#define SWITCH_NOT_PRESSED  (0)					// Nestisknuto

/*************************************************************/
//			Promenne

int update_LCD = 0;
uint32_t freq;
char buf[32];

int main(void)
{

	// inicializace semaforu
	/*
	G_Mutex = xSemaphoreCreateMutex();
	xSemaphoreGive(G_Mutex);
	*/

	// Inicializace A/D prevodniku (potenciometr) - nepouzito

	/*
	ADCInit();

	ADCCalibrate();
	ADCInit();

	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[2] = PORT_PCR_MUX(0);
	*/

	// Inicializace GPIO
	GPIO_Initialize();
	switch_init();

	// Inicializace LCD displeje
    LCD_initialize();
    LCD_clear();
    LCD_set_cursor(1,1);
	LCD_puts("FM Prijimac");
    freq = 920;		// 91.7 radio zlin
    write_freq(freq);

    delay();


	// Inicializace I2C1 driveru
	Driver_I2C1.Initialize(i2c_event);
	Driver_I2C1.PowerControl(ARM_POWER_FULL);
	Driver_I2C1.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);
    delay();

    BaseType_t status;

    status = xTaskCreate(TaskPrint, /* ukazatel na task */
        			"Vypis", /* jmeno tasku pro ladeni - kernel awareness debugging */
        			configMINIMAL_STACK_SIZE +100, /* velikost zasobniku = task stack size */
        			(void*)NULL, /* pripadny parametr pro task = optional task startup argument */
        			tskIDLE_PRIORITY + 1 , /* priorita tasku */
        			(xTaskHandle*)NULL /* pripadne handle na task, pokud ma byt vytvoreno */
        		);
	if ( status != pdPASS)
		while(1) ; /* error! probably out of memory */

    vTaskStartScheduler();
/*
	G_Mutex = xSemaphoreCreateMutex();	//xSemaphoreCreateBinary();
		if ( G_Mutex == NULL ) {
			while(1)
				;		// chyba: nedostatek pameti
		}

		// Semafor je vytvoren "prazdny", musime jej "dat" operacnimu systemu
	xSemaphoreGive(G_Mutex);

	*/

/*

    freq = 917;		// 91.7 radio zlin
    write_freq(freq);

    delay();
    vTaskStartScheduler();
    for (;;) {

    	freq = read_freq();
    	intToStr(freq, buf);
    	LCD_set_cursor(2,1);
    	LCD_puts(buf);
    	intToStr(i, buf);
    	LCD_set_cursor(3,1);
    	LCD_puts(buf);
    	delay();


        i++;
    }*/
    while(1)
    				;		// chyba: nedostatek pameti
    /* Never leave main */
    return 0;
}

void TaskPrint(void * pvParameters){
	for ( ;; ) {

		// Akce se provadi kazdych 600 ms
		vTaskDelay(100 / portTICK_RATE_MS);

		if (update_LCD == 1) {		// pokud je potreba aktualizovat LCD
			xSemaphoreTake(G_Mutex, portMAX_DELAY);
			update_LCD = 0;			// zrusime pozadavek na aktualizaci
			LCD_set_cursor(3,1);	// nastavime kurzor na 3. radek
			print_radio(freq);		// vypiseme nazev stanice
			LCD_set_cursor(4,1);	// nastavime kurzor na 4. radek
			LCD_puts("FREKVENCE:");
			LCD_set_cursor(4,11);	// nastavime kurzor na 4. radek a 10. sloupec
			intToStr(freq, buf);	// prevedeme cislo na retezec
			LCD_puts(buf);			// vypiseme na LCD
			_write_freq(freq);		// zapiseme frekvenci do tuneru
			vTaskDelay(100 / portTICK_RATE_MS);	// cekame 100 ms
			xSemaphoreGive(G_Mutex);// uvolnime semafor
		}

		delay();
	}
}

void print_radio(uint32_t freq) {
	if (895 < freq && freq < 900) {		//  895
		LCD_puts("Rock Radio       ");
	}
	else if (920 < freq && freq < 925) {		//  920
		LCD_puts("Radio Zlin       ");
	}
	else if (941 < freq && freq < 945) {		//  943
		LCD_puts("Radio Blanik     ");
	}
	else if (973 < freq && freq < 978) {		//  975
		LCD_puts("Radio Zlin       ");
	}
	else
		LCD_puts("                 ");
}

void TaskReadButtons (void* pvParameters){
	for (;;){
		if( switch_readw(SW1) == SWITCH_PRESSED ) {
			xSemaphoreTake(G_Mutex, portMAX_DELAY);
			freq = 895;		// 89.5 Rock Radio
			update_LCD = 1;
			xSemaphoreGive(G_Mutex);
		}
		if( switch_readw(SW2) == SWITCH_PRESSED ) {
			xSemaphoreTake(G_Mutex, portMAX_DELAY);
			freq = 917;		// 91.7 Radio Zlin
			update_LCD = 1;
			xSemaphoreGive(G_Mutex);
		}
		if( switch_readw(SW3) == SWITCH_PRESSED ) {
			xSemaphoreTake(G_Mutex, portMAX_DELAY);
			freq = 943;		// 94.3 Radio Blanik
			update_LCD = 1;
			xSemaphoreGive(G_Mutex);
		}
		if( switch_readw(SW4) == SWITCH_PRESSED ) {
			xSemaphoreTake(G_Mutex, portMAX_DELAY);
			freq = 975;		// 97.5 Radio Zlin
			update_LCD = 1;
			xSemaphoreGive(G_Mutex);
		}

	}
}

void intToStr(int N, char *str) {
    int i = 0;

    // Save the copy of the number for sign
    int sign = N;

    // If the number is negative, make it positive
    if (N < 0)
        N = -N;

    // Extract digits from the number and add them to the
    // string
    while (N > 0) {

        // Convert integer digit to character and store
      	// it in the str
        str[i++] = N % 10 + '0';
      	N /= 10;
    }

    // If the number was negative, add a minus sign to the
    // string
    if (sign < 0) {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

void delay(void)
{
	unsigned long n = 300000L;
	while ( n-- )
		;
}

void switch_init(void)
{
	// Nastavit piny pro SW1-SW4 jako vstup s povolenym pull-up rezistorem
	pinMode(SW1, INPUT_PULLUP);
	pinMode(SW2, INPUT_PULLUP);
	pinMode(SW3, INPUT_PULLUP);
	pinMode(SW4, INPUT_PULLUP);
}

int switch_readw(int SW)
{
    int switch_state = SWITCH_NOT_PRESSED;
    if ( pinRead(SW) == LOW )
    {
        // tlacitko je stisknuto

        // debounce = wait
        delay_debounce();

        // znovu zkontrolovat stav tlacitka
        if ( pinRead(SW) == LOW )
        {
        	// cekame na uvolneni tlacitka
        	while( pinRead(SW) == LOW )
        		;
            switch_state = SWITCH_PRESSED;
        }
    }
    // vratime stav tlacitka
    return switch_state;
}

// Cte frekvenci nastavenou v obvodu FM tuneru
// Vraci: frekvence * 10 tj. napr. pro 98 MHz vrati 980
uint32_t read_freq(void)
{
	ARM_I2C_STATUS status;
	uint8_t data[6];

	// Vzdy cteme 5 bajtu
	Driver_I2C1.MasterReceive(I2C_ADR_FM_TUNER, data, 5, false);
	status = Driver_I2C1.GetStatus();
	while (status.busy)
		status = Driver_I2C1.GetStatus();

	freq=(((((data[0]&0x3F)<<8)+data[1])+1)*32768/4-225000)/100000;
	return freq;

}


// Zapise do obvodu FM tuneru novou frekvenci, tj. preladi na danou frekvenci.
// Vstup: frekvence v MHz * 10 tj. pro 95 MHz se funkci preda freq = 950
void write_freq(uint32_t freq)
{
	ARM_I2C_STATUS status;
	uint8_t buffer[6];
	uint16_t freq14bit;
	uint8_t freqH, freqL;

	if ((freq >= 700) && (freq <= 1080)) {
		//rozlozeni frekvence na dva bajty tzv PLL word (14 bitu)
		// vzorec odpovida HIGH side injection
		freq14bit = (4 * (freq * 100000 + 225000) / 32768) + 1;
		freqH = (freq14bit >> 8);
		freqL = (freq14bit & 0xFF);
		//buffer[0] = 0x00;
		buffer[0] = freqH;
		buffer[1] = freqL;
		// Dalsi hodnoty jsou v puvodnim ovladaci uz v promenne buffer,
		// protoze jsou nastaveny v init
		buffer[2]=  0b10110000;		// arduino = hc = 0b10110000;
		// Dle datasheet pro Byte 3: nutno nastavit bit 4 = high side injection
		// tj. 0x10
		// Bit 7 = 1 > search up
		// Bit 6,7 = search stop level; 01 = LOW
		// Hodnota 0xB0 = 0b10110000 je ok :)

		// Hodnoty pro byte 4:
		// Bit 4 (XTAL) = frekvence krystalu spolu s bitem 7 v byte 5 = PLLREF
		// Hodnota PLLREF = 0 a XTAL = 1 odpovida 32,768 kHz
		// Arduino 0x10 nastavuje jen XTAL, HC verze zapina i noise cancel a high cut...
		buffer[3]=  0x10;		// arduino: 0x10; hc: 0b00010110;
		buffer[4] = 0;			// 0 je ok (PLLREF = 0)

		// Odesilame 5 bajtu a cekame na odeslani
		Driver_I2C1.MasterTransmit(I2C_ADR_FM_TUNER, buffer, 5, false);
		status = Driver_I2C1.GetStatus();
		while (status.busy) {
			status = Driver_I2C1.GetStatus();
		}

	}

	/* Arduino:
		 frequency=87.5; //starting frequency
		 frequencyB=4*(frequency*1000000+225000)/32768; //calculating PLL word
		 frequencyH=frequencyB>>8;
		 frequencyL=frequencyB&0XFF;
		 Wire.beginTransmission(0x60);   //writing TEA5767
		 Wire.write(frequencyH);
		 Wire.write(frequencyL);
		 Wire.write(0xB0);
		 Wire.write(0x10);
		 Wire.write(0x00);
		 Wire.endTransmission();
		 */
}






////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
