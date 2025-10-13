

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "delay.h"

#define PCTIM2 22
#define PCLK_TIMER2 12
#define TCR_RESET 1
#define TCR_ENABLE 0

#define SYSTICK_FREQ (SystemCoreClock / 1000)
static volatile uint32_t tick;

void SysTick_Handler(void) {
	tick++;
}

/* Faz a iniciação do temporizador para ter a resolução de 1ms e o Timer2. */
int DELAY_Init(void){
    SystemCoreClockUpdate();
    return (SysTick_Config(SYSTICK_FREQ) == 1) ? -1 : 0;

    // Inicializar o TIMER2
    LPC_SC -> PCONP |= (1 << PCTIM2);
    LPC_SC -> PCLKSEL1 = (3 << PCLK_TIMER2);

	// Reset ao counter
	LPC_TIM2 -> TCR = (1 << TCR_RESET);

	// 1 us
	LPC_TIM2 -> PR = (SystemCoreClock/1000)/1000;

	// IR = 1  para "limpar" e "voltar" a contar
	LPC_TIM2 -> IR = 1;
}

/* Espera o número de milissegundos que são passados no parâmetro millis. */
void DELAY_Milliseconds(uint32_t millis){
    uint32_t start = tick;
    while ((tick - start) < millis) {
    	__WFI();
    }
}

/* Devolve , em milissegundos, a diferença do valor passado em start para o tempo atual. */
uint32_t DELAY_GetElapsedMillis(uint32_t start){
    return tick - start;
}

/* Utilizando o Timer2 espera em microsegundos o valor passado no parâmetro. */
void DELAY_Microseconds(uint32_t waitUs){

	// Definir os MATCHs
	LPC_TIM2 -> MR0 = waitUs;
	LPC_TIM2 -> MCR = 1;

	// Enable ao counter
	LPC_TIM2 -> TCR = (1 << TCR_ENABLE);

	// Esperar IR
	while (LPC_TIM2 -> IR != 1){
		__WFI();
	}

	// IR = 1  para "limpar" e "voltar" a contar
	LPC_TIM2 -> IR = 1;

	// Reset ao counter
	LPC_TIM2 -> TCR = (1 << TCR_RESET);

}
