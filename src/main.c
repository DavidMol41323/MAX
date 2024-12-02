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

    GPIO_Init(DIN_PORT, DIN_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CS_PORT,CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CLK_PORT, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
#if defined (BTN_PORT) || defined (BTN_PIN)
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);
#endif

    init_milis();
    //init_uart1();
}


int main(void)
{

    init();

    while (1) {



    }
}
/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
