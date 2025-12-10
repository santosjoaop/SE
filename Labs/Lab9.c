/**
 * @file Lab9.c
 * @author Grupo 2
 * @brief Antena 1 Tuner
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>
#include <stdio.h>
#include "delay.h"
#include "lcd.h"
#include "radio.h" // Certifique-se que radio.h tem as declarações novas

int main(void){
    uint16_t data;

    // 1. Inicializações
    DELAY_Init();
    LCDText_Init();

    LCDText_Printf("Iniciando...");

    // Radio_Init agora faz o reset hardware e setup inicial
    Radio_Init();
    Radio_SHUTDOWN(0);

    // 2. Configurar Volume (0 a 15)
    Radio_SetVolume(3); // Volume alto mas não maximo

    // 3. Sintonizar 95.7 MHz (Antena 1)
    // A função SetFreq faz o cálculo correto: (95.7 - 87) / 0.1 = Channel 87
    Radio_SetFreq(95.7);

    // 4. Interface
    LCDText_Clear();
    LCDText_Printf("Antena 1 95.7");

    // 5. Debug / Loop
    while(1) {
        // Ler RSSI (Signal Strength) do registo 0x0B
        // O Reg 0x0B tem o RSSI nos bits [15:9]
        Radio_Read_Word(0x0B, &data);
        uint8_t rssi = data >> 9;

        // (Opcional) Mostrar RSSI no LCD para ver se apanhou sinal
        // LCDText_SetCursor(2, 0); // Exemplo se o LCD tiver essa func
        LCDText_Printf("\nRSSI:%d", rssi);

        DELAY_Milliseconds(1000);
    }
}
