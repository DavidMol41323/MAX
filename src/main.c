#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
#include "delay.h"
//#include "uart1.h"


void max7219_send(uint8_t address, uint8_t data)
{
    uint8_t mask; // pomocná proměnná, která bude sloužit k procházení dat bit po bitu
    CS_LOW;       // nastavíme linku LOAD/CS do úrovně Low (abychom po zapsání všech 16ti bytů mohli vygenerovat na CS vzestupnou hranu)

    
    mask = 0b10000000;       // nejprve odešleme prvních 8bitů zprávy (adresa/příkaz)
    CLK_LOW;          
    while (mask)             // dokud jsme neposlali všech 8 bitů
    { 
        if (mask & address)  // pokud má právě vysílaný bit hodnotu 1
        {              
            DATA_HIGH;
        }
        else
        {             
            DATA_LOW; 
        }
        CLK_HIGH;            // přejdeme na CLK z úrovně Low do úrovně High, a budič si zapíše hodnotu bitu, kterou jsme nastavili na DIN
        mask = mask >> 1;    // rotujeme masku abychom v příštím kroku vysílali nižší bit
        CLK_LOW;             // vrátíme CLK zpět do Low abychom mohli celý proces vysílání bitu opakovat
    }

   
    mask = 0b10000000;       // poté pošleme dolních 8 bitů zprávy (data/argument)
    while (mask)             // dokud jsme neposlali všech 8 bitů
    {
        if (mask & data)     // pokud má právě vysílaný bit hodnotu 1
        {              
            DATA_HIGH; 
        }
        else
        {             
            DATA_LOW;
        }
        CLK_HIGH;            // přejdeme na CLK z úrovně Low do úrovně High, a budič si zapíše hodnotu bitu, kterou jsme nastavili na DIN
        mask = mask >> 1;    // rotujeme masku abychom v příštím kroku vysílali nižší bit
        CLK_LOW;             // vrátíme CLK zpět do Low abychom mohli celý proces vysílání bitu opakovat
    }

    CS_HIGH; 
}

void TIM2_init(void)
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2,ENABLE);
    TIM2_TimeBaseInit(TIM2_PRESCALER_16,999);
    TIM2_ClearFlag(TIM2_FLAG_UPDATE);
    TIM2_ITConfig(TIM2_IT_UPDATE,ENABLE);
    TIM2_Cmd(ENABLE);
}

void max7219_init(void){
    GPIO_Init(DATA_PORT, DATA_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CS_PORT, CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CLK_PORT, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

    // Nastavení parametrů budiče
    max7219_send(DECODE_MODE, DECODE_ALL); // Nechceme dekódování pro znaky
    max7219_send(SCAN_LIMIT, 3); // Velikost displeje 8 cifr    (5 pro minuty)
    max7219_send(INTENSITY, 2); // Jas, 0-15 (0 je nejnižší)
    max7219_send(DISPLAY_TEST, DISPLAY_TEST_OFF); // Vypnout testovací režim
    max7219_send(SHUTDOWN, DISPLAY_ON); // Zapnout displej (SHUTDOWN mode)
}

void init(void){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktování MCU na 16MHz
    
    init_milis();
    max7219_init();
    enableInterrupts();
    TIM2_init();
}

int main(void)
{
    init(); // Iniciace MAX7219
    max7219_send(DIGIT0, 0);
    max7219_send(DIGIT1, 0);
    max7219_send(DIGIT2, 0);
    max7219_send(DIGIT3, 0);
    max7219_send(DIGIT4, 0);
    max7219_send(DIGIT5, 0);
    max7219_send(DIGIT6, 0);
    max7219_send(DIGIT7, 0);

    uint32_t milis_time = 0;
    uint32_t my_time = 0;
    uint32_t time = 0;
    uint8_t digit0 = 0;
    uint8_t digit1 = 0;
    uint8_t digit2 = 0;
    uint8_t digit3 = 0;
    uint8_t digit4 = 0;
    uint8_t digit5 = 0;

    while (1){
        milis_time = milis();

        if((milis_time-time) > 4000){ // 4000 = 1 sekudna
            time = milis_time;
            
            max7219_send(DIGIT0, digit0);
            max7219_send(DIGIT1, digit1);
            max7219_send(DIGIT2, digit2);
            max7219_send(DIGIT3, digit3);
            max7219_send(DIGIT4, digit4);
            max7219_send(DIGIT5, digit5);
            
            digit0++;

            if(digit0>9){
                digit1++;
                digit0 = 0;
            }

            if(digit1>9){
                digit2++;
                digit1 = 0;
            }
    
            if(digit2>9){
                digit3++;
                digit2 = 0;
            }

            if(digit3>5){
                digit4++;
                digit3 = 0;
                digit2 = 0;
                digit1 = 0;
                digit0 = 0;
            }
/*          // Pro minuty
            if(digit3>5){
                digit4++;
                digit3 = 0;
            }

            if(digit4>9){
                digit5++;
                digit4 = 0;
            }

            if(digit5>5){
                digit0 = 0;
                digit1 = 0;
                digit2 = 0;
                digit3 = 0;
                digit4 = 0;
                digit5 = 0;
            } */
        }
    }

}


/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
