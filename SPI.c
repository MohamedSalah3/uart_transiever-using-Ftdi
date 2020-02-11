/*
* SPI.c
*/
#include "SPI.h"
#include "avr/io.h"
#include "avr/interrupt.h"

extern ST_SPI_Configuration_t SPI_Config ;

static void (*SPI_ISR)(void);

void SPI_Init()
{

 ST_SPI_Configuration_t *gConfig = & SPI_Config;

if (gConfig->DATA_ORDER == SPI_LSB_FISRT)
	SetBit(SPCR, DORD);
else if (gConfig->DATA_ORDER == SPI_MSB_FISRT)
	ClearBit(SPCR, DORD);

if (gConfig->SLAVE_MODE == SPI_MASTER)
	SetBit(SPCR, MSTR);

else if (gConfig->SLAVE_MODE == SPI_SLAVE)
	ClearBit(SPCR, MSTR);

if (gConfig->OPERATING_LEVEL == SPI_IDLE_LOW)
	SetBit(SPCR, CPOL);
else if (gConfig->OPERATING_LEVEL == SPI_IDLE_HIGH)
	ClearBit(SPCR, CPOL);

if (gConfig->SAMPLING_EDGE == SPI_RISING)
	SetBit(SPCR, CPHA);

else if (gConfig->SAMPLING_EDGE == SPI_FALLING)
	ClearBit(SPCR, CPHA);

	SPCR = SPCR | (gConfig->PRESCALAR);

	if (gConfig->DOUBLE_SPEED == SPI_DOUBLE_SPEED_MODE_ON)
		SetBit(SPSR, SPI2X);

	else if (gConfig->DOUBLE_SPEED == SPI_DOUBLE_SPEED_MODE_OFF)
		ClearBit(SPSR, SPI2X);

	if (gConfig->ENABLE == SPI_ENABLE_ON)
		SetBit(SPCR, SPE);

	else if (gConfig->ENABLE == SPI_ENABLE_OFF)
		ClearBit(SPCR, SPE);
}



uint8_t  SPI_Send_And_receive(uint8_t u8_data)
{
   /* Start transmission */
   SPDR = u8_data;
   /* Wait for transmission complete */
   while(!(SPSR & (1<<SPIF)))
   ;
   //return SPDR ; // Received data
   return 1;
}

uint8_t SPI_Checks_for_collision(void)
{
 return GetBit(SPSR, WCOL);
}


void SPI_callBackFunc_Assign(void (*PtrToSPI_Isr) (void))
{
	SPI_ISR = PtrToSPI_Isr;
}

ISR(SPI_STC_vect)
{
	SPI_ISR();
}
