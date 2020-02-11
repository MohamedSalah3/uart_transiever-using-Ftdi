/*
 * SPI.h
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_

#include "std_types.h"
#include "SPI_Config.h"
#include "registers.h"
#define SPIE 	7
#define SPE 	6
#define DORD 	5
#define MSTR 	4
#define CPOL 	3
#define CPHA 	2
#define SPR1	1
#define SPR0	0

#define SPIF	7
#define WCOL	6
#define SPI2X	0

#define OK  1
#define ERR 0

 void     SPI_Init();
 uint8_t  SPI_Send_And_receive(uint8_t u8Data);
 uint8_t  SPI_Checks_for_collision(void);
 void     SPI_callBackFunc_Assign(void(*PtrToSPI_Isr)(void));

#endif /* SPI_SPI_H_ */
