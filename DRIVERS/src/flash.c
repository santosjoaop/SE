/**
 * @file flash.c
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
#include "delay.h"
#include "lcd.h"
#include <stdio.h>

#define IAP_LOCATION 0x1FFF1FF1
typedef void (*IAP)(unsigned int [],unsigned int[]);
static IAP iap_entry = (IAP)IAP_LOCATION;



unsigned int FLASH_EraseSector(unsigned int sector){
	 unsigned int OUT[5];

	//prepare for write/erase
	unsigned int IN[5] = {50, sector, sector};
	iap_entry(IN, OUT);
	if(OUT[0] != 0) return OUT[0];

	//clearing the sector
	unsigned int IN2[5] = {52, sector, sector, SystemCoreClock};
	iap_entry(IN2, OUT);
	return OUT[0];
}


unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size){
	unsigned int OUT[5];
	//aqui o sector da flash já está preparado para escrita

	///CUIDADO com size("Number of bytes to be written. Should be 256 | 512 | 1024 | 4096");
	//writing data from RAM to FLASH
	unsigned int IN[5] = {51, (unsigned int)dstAddr, (unsigned int)srcAddr, size, SystemCoreClock};
	iap_entry(IN, OUT);
	return OUT[0];
}


unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size){
	unsigned int OUT[5];

	///CUIDADO com size("Number of bytes to be compared; should be a multiple of 4");
	//cmp entre RAM/flash e RAM/flash
	unsigned int IN[5] = {56, (unsigned int)dstAddr, (unsigned int)srcAddr, size};
	iap_entry(IN, OUT);
	return OUT[0];
}



