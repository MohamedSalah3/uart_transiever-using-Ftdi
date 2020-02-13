/*
 * uart.h
 *
 * Created: 10/02/2020 08:02:37 م
 *  Author: mo
 */


#ifndef UART_H_
#define UART_H_
#include "uartconfig.h"
#include "registers.h"
#include "std_types.h"
extern void Uart_Init(En_BAUD_Rate Baud_rate,En_Stop_config Stop_bits_num,
EN_Parity parity_Bit,EN_Data_Size data_num_bits,EN_UartMode uart_mode);
extern void UartTransmitInterrupt(void);
extern void UartRecieveInterrupt(void);
extern void UartTransmitPooling(uint8_t Data);
extern uint8_t UartRecievePooling(void);
extern void Enable_recieve_interrupt(void);

#endif /* UART_H_ */
