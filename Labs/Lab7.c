/**
 * @file Lab7.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-11-16
 *
 * @copyright Copyright (c) 2025
 * 
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "delay.h"
#include "flash.h"


#define ADDR_START_SECTOR_29 0x00078000
#define ADDR_END_SECTOR_29 0x0007FFFF


int main(void) {
    printf("Hello World\n");

    DELAY_Init();
    LCDText_Init();


    int save = 1;
    if(save){
		Struct_Grupo data;
		data.group = 2;
		strcpy(data.name1, "Freixo");
		strcpy(data.name2, "Santos");

		uint8_t buffer[256] = {0};
		memcpy(buffer, &data, sizeof(data));
		FLASH_EraseSector(29);
		FLASH_WriteData((void*)ADDR_START_SECTOR_29, buffer, sizeof(buffer));
		if(FLASH_VerifyData((void*)ADDR_START_SECTOR_29, buffer, sizeof(buffer))== 0){
			printf("Dados gravados");
		}
    }


    else{
		Struct_Grupo data_flash;
		uint8_t buffer_flash[256] = {0};
		memcpy(buffer_flash, &data_flash, sizeof(data_flash));
		FLASH_WriteData(&data_flash, (void*)ADDR_START_SECTOR_29, sizeof(buffer_flash));
		if(FLASH_VerifyData(&data_flash, (void*)ADDR_START_SECTOR_29, sizeof(buffer_flash))== 0){
			LCDText_Printf("Grupo:%d\n%s %s", data_flash.group, data_flash.name1, data_flash.name2);
		}
    }

}
