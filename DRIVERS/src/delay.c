
/* Faz a iniciação do temporizador para ter a resolução de 1ms e o Timer2. */
int DELAY_Init(void){
    SystemCoreClockUpdate();
    return (SysTick_Config(SYSTICK_FREQ) == 1) ? -1 : 0;
}

    

/* Espera o número de milissegundos que são passados no parâmetro millis. */
void DELAY_Milliseconds(uint32_t millis){
    uint32_t start = tick;
    while (tick - start) < millis) {
        __WFI();
    }
}

    
/* Devolve , em milissegundos, a diferença do valor passado em start para o tempo atual. */
uint32_t DELAY_GetElapsedMillis(uint32_t start){
    return tick - start;
}
    
/* Utilizando o Timer2 espera em microsegundos o valor passado no parâmetro. */
void DELAY_Microseconds(uint32_t waitUs);

