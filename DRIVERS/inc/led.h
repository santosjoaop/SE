//DESCRIÇAO DOXYGEN SAMPAIO



/* Faz a iniciação do sistema para permitir a manipulação do estado LED do sistema de
 * protopagem (LPCXPRESSO LPC1769), onde o parâmetro state se igual a false o LED
 * fica apagado ou caso contrario fica aceso. */
void LED_Init(bool state);
/* Devolve true se o LED está aceso e false se o LED está apagado. */
bool LED_GetState(void);
/* Acende o LED. */
void LED_On(void);
/* Apaga o LED. */
void LED_Off(void);
/* Troca o estado do LED. Se estiver aceso apaga o LED, caso contrario acende o LED. */
void LED_Toggle(void);
