#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "delay.h"
#include "i2c.h"
#include "radio.h"

// Memória local para guardar o estado dos registos (Shadow Registers)
// Isto impede que o código escreva lixo no rádio
static uint16_t shadow_regs[16];

#define P021 21

int Radio_Init(void){
    I2CMASTER_Init();
    I2CMASTER_SetFrequency(100000);

    // 1. Reset Hardware (Pino 21)
    LPC_GPIO0->FIODIR |= (1 << P021);

    LPC_GPIO0->FIOCLR = (1 << P021); // Reset (0V)
    DELAY_Milliseconds(10);
    LPC_GPIO0->FIOSET = (1 << P021); // Liga (3.3V)
    DELAY_Milliseconds(50);

    // 2. Definir valores iniciais corretos na memória
    shadow_regs[2] = 0xC001; // Enable=1, DMute=1, DHIZ=1
    shadow_regs[3] = 0x0000;
    shadow_regs[4] = 0x0000;
    shadow_regs[5] = 0x880F; // Volume Max (0x0F)
    shadow_regs[6] = 0x0000;
    shadow_regs[7] = 0x4202;

    // Escrever a configuração inicial de Power On
    Radio_Write_Word(0x02, shadow_regs[2]);

    return 0;
}

int Radio_Write_Word(uint8_t reg, uint16_t data)
{
    // 1. Guardar o valor na nossa memória local
    if(reg >= 2 && reg <= 7) {
        shadow_regs[reg] = data;
    }

    // 2. Preparar buffer: Reg Address + High Byte + Low Byte
    uint8_t buffer[3];
    buffer[0] = reg;
    buffer[1] = data >> 8;
    buffer[2] = data & 0xFF;

    // 3. Enviar apenas este registo (Random Access Write)
    I2CMASTER_Transmit(0x11, buffer, 3);

    return 0;
}

int Radio_Read_Word(uint8_t reg, uint16_t *data)
{
    // Leitura simples (Status)
    uint8_t regAddr = reg;
    I2CMASTER_Transmit(0x11, &regAddr, 1);

    uint8_t buf[2];
    if(I2CMASTER_Receive(0x11, buf, 2) == 0){
        *data = (buf[0] << 8) | buf[1];
        return 0;
    }
    return -1;
}

// Cálculo corrigido para 95.7
int Radio_SetFreq(float freq){
    // Fórmula: (Frequencia - 87.0) * 10
    // Ex: (95.7 - 87.0) = 8.7 -> * 10 = 87
    uint16_t channel = (uint16_t)((freq - 87.0f) * 10.0f);

    // Montar Registo 03:
    // Bit 15-6: Channel
    // Bit 4: TUNE (Obrigatorio ser 1 para mudar a estacao)
    // Bit 3-2: Band (00 = 87-108MHz)
    // Bit 1-0: Space (00 = 100kHz)
    uint16_t reg03 = (channel << 6) | (1 << 4);

    // Guardar e escrever
    Radio_Write_Word(0x03, reg03);

    DELAY_Milliseconds(50); // Tempo para PLL travar

    return 0;
}

int Radio_SetVolume(int volume){
    if(volume > 15) volume = 15;

    // Recuperar o valor atual do Reg 05 da memória shadow
    uint16_t reg05 = shadow_regs[5];

    // Limpar os 4 bits de volume (0x000F) e aplicar novo
    reg05 &= 0xFFF0;
    reg05 |= volume;

    Radio_Write_Word(0x05, reg05);
    return 0;
}

int Radio_SHUTDOWN(int on){
    if(on) LPC_GPIO0 -> FIOSET = (1<<P021);
    else   LPC_GPIO0 -> FIOCLR = (1<<P021);
    return on;
}
