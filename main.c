/*
 * UART.c
 *
 * Created: 10/02/2020 08:00:40 م
 *  Author: mo
 */
#include "pushButtonConfig.h"
#include "pushButton.h"
#include "led.h"
#include "ledConfig.h"
#include "timers.h"
#include "uart.h"
#include "uartconfig.h"
int main(void)
{	uint8_t loop=0;
	uint8_t data_sent='1';
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	SPI_Init();
	Led_Init(LED_0);
	Led_Init(LED_1);
		timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_NO,0,0,0,T2_POLLING);
	Uart_Init(Baud9600,OneStopBit,NoParity,EightBits,ASynchronous);
	Led_On(LED_0);
    Led_On(LED_1);
	data_sent=UartRecievePooling();
    while(1)
    {

		if (pushButtonGetStatus(BTN_0))
		{

		data_sent++;
		}
		if (pushButtonGetStatus(BTN_1))
		{

			data_sent--;
		}
		UartTransmitPooling(data_sent);
		SPI_Send(data_sent);
		timer2Start();
		timer2DelayMs(100);

		}
  

}

	