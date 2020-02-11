/*
 * UART.c
 *
 * Created: 10/02/2020 08:00:40 م
 *  Author: mo
 */
#include "led.h"
#include "ledConfig.h"
#include "timers.h"
#include "uart.h"
#include "uartconfig.h"
int main(void)
{Led_Init(LED_0);
	Led_Init(LED_1);
	uint8_t data_sent='Z';
	timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_NO,0,0,0,T2_POLLING);
  Uart_Init(Baud9600,OneStopBit,NoParity,EightBits,ASynchronous);
  Led_On(LED_0);
      while(1)
    {
		Led_On(LED_1);
		timer2Start();
		timer2DelayMs(1000);
      UartTransmitPooling(data_sent);
	
	if (UartRecievePooling() == 'z')
	{
		Led_Toggle(LED_0);
		Led_Toggle(LED_1);
		timer2Start();
		timer2DelayMs(1000);
		
	}
		 
	 }
}
