#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
//#include "delay.h"
//#include "uart1.h"

void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz

    GPIO_Init(DATA_PORT, DATA_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CS_PORT,CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CLK_PORT, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

    // nastavíme základní parametry budiče
    max7219_posli(DECODE_MODE, DECODE_ALL); // zapnout znakovou sadu na všech cifrách
    max7219_posli(SCAN_LIMIT, 7); // velikost displeje 8 cifer (počítáno od nuly, proto je argument číslo 7)
    max7219_posli(INTENSITY, 5); // volíme ze začátku nízký jas (vysoký jas může mít velkou spotřebu - až 0.25A !)
    max7219_posli(DISPLAY_TEST, DISPLAY_TEST_OFF); // Funkci "test" nechceme mít zapnutou
    max7219_posli(SHUTDOWN, DISPLAY_ON); // zapneme displej

    init_milis();
    //init_uart1();
}

void max7219_send(uint8_t adress, uint8_t data){
    uint8_t maska;
    CS_LOW; //Nastavení LOAD na low

    maska= 0b100000000; //Odeslání prvních 8 bitů (adresa)
    CLK_LOW; //Nastavení CLK na low

    while(maska){ //dokud jsme neposlali všech 8 bitů
        if(maska & adress){ //Pokud je právě vysílaný bit 1
        DATA_HIGH;
        }
        else{ //Pokud je právě vysílaný bit 0
            DATA_LOW;
        }
        CLK_HIGH;
        maska= maska>>1 // rotujeme masku abychom v příštím kroku vysílali nižší bit
        CLK_LOW
    }
    maska= 0b10000000; //Odeslání dolních 8 bitů (data)
    while(maska){ //dokud jsme neposlali všech 8 bitů
        if(maska & adress){ //Pokud je právě vysílaný bit 1
        DATA_HIGH;
        }
        else{ //Pokud je právě vysílaný bit 0
            DATA_LOW;
        }
        CLK_HIGH;
        maska= maska>>1 // rotujeme masku abychom v příštím kroku vysílali nižší bit
        CLK_LOW
    }
    CS_HIGH;
}

int main(void)
{
    init();
    max7219_send(DIGIT0, 2)
}
/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
