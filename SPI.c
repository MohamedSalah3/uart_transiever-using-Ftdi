/*
 * SPI.c
 *
 * Created: 2/8/2020 10:15:20 PM
 * Author : EbrahimOseif
 */
#include "SPI.h"
#include "registers.h"
#include "gpio.h"
#include "avr/interrupt.h"



extern ST_SPI_Configuration SPI_Config ;
/*
static void (*SPI_ISR)(void);
*/
void SPI_Init()
{
	
	 ST_SPI_Configuration *gConfig = & SPI_Config;
		
	/********************Enable SPI Interrupt ******************/
		
	//SPCR = SPCR | (SPI_INT_ENABLE<<SPIE);
	SPCR =   gConfig->MASTER_SLAVE_MODE | gConfig->DATA_ORDER 
			  | gConfig->OPERATING_LEVEL | gConfig->PRESCALAR 
			 | gConfig->SAMPLING_EDGE;
			 
	SPSR |=  gConfig->DOUBLE_SPEED;
			 gpioPinDirection(GPIOB, BIT4 | BIT5 | BIT7, OUTPUT);
			 gpioPinDirection(GPIOB, BIT6, INPUT);
			 
		SPCR |=  gConfig->ENABLE;

   
		
}



void  SPI_Send(uint8_t u8_data)
{
     /* Start transmission */
     SPDR = u8_data;
     /* Wait for transmission complete */
     while(!(SPSR & (1<<SPIF)))
     ;
}

uint8_t  SPI_Receive(void)
{
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
	//return SPDR ; // Received data
	return SPDR;
}


 uint8_t SPI_Checks_for_collision(void)
{
	 return READBIT(SPSR, WCOL); 
}

/*
  void SPI_callBackFunc_Assign(void (*PtrToSPI_Isr) (void))
 {
 	SPI_ISR = PtrToSPI_Isr;
 }


  ISR(SPI_STC_vect)
  {
  	SPI_ISR();
  }

*/