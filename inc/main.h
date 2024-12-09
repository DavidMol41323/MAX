#ifndef _MAIN_H_
#define _MAIN_H_ 1

extern uint32_t my_time; //vlastní milis

#define LOW(BAGR) GPIO_WriteLow(BAGR##_PORT, BAGR##_PIN)
#define HIGH(BAGR) GPIO_WriteHigh(BAGR##_PORT, BAGR##_PIN)
#define REVERSE(BAGR) GPIO_WriteReverse(BAGR##_PORT, BAGR##_PIN)

#define READ(BAGR) (GPIO_ReadInputPin(BAGR##_PORT, BAGR##_PIN)!=RESET) 
#define PUSH(BAGR) (GPIO_ReadInputPin(BAGR##_PORT, BAGR##_PIN)==RESET) 

//Definování portů
#define DATA_PORT GPIOC
#define DATA_PIN GPIO_PIN_5

#define CS_PORT GPIOC
#define CS_PIN GPIO_PIN_7

#define CLK_PORT GPIOC
#define CLK_PIN GPIO_PIN_6

//definování HIGH a LOW
#define CLK_HIGH GPIO_WriteHigh(CLK_PORT, CLK_PIN)
#define CLK_LOW  GPIO_WriteLow(CLK_PORT, CLK_PIN)
#define DATA_HIGH GPIO_WriteHigh(DATA_PORT, DATA_PIN)
#define DATA_LOW  GPIO_WriteLow(DATA_PORT, DATA_PIN)
#define CS_HIGH GPIO_WriteHigh(CS_PORT, CS_PIN)
#define CS_LOW  GPIO_WriteLow(CS_PORT, CS_PIN)


// makra adres/příkazů pro čitelnější ovládání MAX7219
#define NOOP 		 0   // No operation
#define DIGIT0 		 1	 // zápis hodnoty na 1. cifru
#define DIGIT1 		 2	 // zápis hodnoty na 2. cifru
#define DIGIT2 		 3	 // zápis hodnoty na 3. cifru
#define DIGIT3 		 4	 // zápis hodnoty na 4. cifru
#define DIGIT4 		 5	 // zápis hodnoty na 5. cifru
#define DIGIT5 		 6	 // zápis hodnoty na 6. cifru
#define DIGIT6 		 7	 // zápis hodnoty na 7. cifru
#define DIGIT7 		 8	 // zápis hodnoty na 8. cifru
#define DECODE_MODE  9	 // Aktivace/Deaktivace znakové sady (my volíme vždy hodnotu DECODE_ALL)
#define INTENSITY 	 10	 // Nastavení jasu - argument je číslo 0 až 15 (větší číslo větší jas)
#define SCAN_LIMIT 	 11	 // Volba počtu cifer (velikosti displeje) - argument je číslo 0 až 7 (my dáváme vždy 7)
#define SHUTDOWN 	 12	 // Aktivace/Deaktivace displeje (ON / OFF)
#define DISPLAY_TEST 15	 // Aktivace/Deaktivace "testu" (rozsvítí všechny segmenty)

// argumenty pro SHUTDOWN
#define DISPLAY_ON		1	// zapne displej
#define DISPLAY_OFF		0	// vypne displej
// argumenty pro DISPLAY_TEST
#define DISPLAY_TEST_ON 	1	// zapne test displeje
#define DISPLAY_TEST_OFF 	0	// vypne test displeje
// argumenty pro DECODE_MOD
#define DECODE_ALL		0b11111111 // (lepší zápis 0xff) zapíná znakovou sadu pro všechny cifry
#define DECODE_NONE		0 // vypíná znakovou sadu pro všechny cifry

// Discovery Board
#ifdef STM8S003
#define LED_PORT GPIOD
#define LED_PIN  GPIO_PIN_0
#define BTN_PORT GPIOB
#define BTN_PIN  GPIO_PIN_7
#endif

// Dero Board
#ifdef STM8S103
#define LED_PORT GPIOD
#define LED_PIN  GPIO_PIN_4
#endif

// Discovery Board
#ifdef STM8S105
#define LED_PORT GPIOD
#define LED_PIN  GPIO_PIN_0
#endif

// Nucleo Kit
#ifdef STM8S208
#define LED_PORT GPIOC
#define LED_PIN  GPIO_PIN_5
#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4
#endif

// functions
void init(void);
void max7219_send(uint8_t adress, uint8_t data);


#endif // !_MAIN_H_
