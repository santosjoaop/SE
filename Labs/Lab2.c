#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "led.h"
#include "delay.h"


#define BLINK_TIME 5000
#define OFF_TIME 2000
#define LED_PERIOD 500000 //0,5s = 500ms = 500000 us


int main(void) {
    printf("Hello World\n");

    LED_Init(true);
    while(1){
    	// Tempo atual
    	int tempo_atual = DELAY_GetElapsedMillis(0);
    	while(DELAY_GetElapsedMillis(tempo_atual) <= BLINK_TIME){	//Ou então podemos fazer toogle e delay???

    		LED_On();
    		DELAY_Microseconds(LED_PERIOD);
    		LED_Off();
    		DELAY_Microseconds(LED_PERIOD);

    	}
    	int tempo_passado = DELAY_GetElapsedMillis(0);
    	while(DELAY_GetElapsedMillis(tempo_passado) <= OFF_TIME){
    		LED_Off();
    	}

    }

}
