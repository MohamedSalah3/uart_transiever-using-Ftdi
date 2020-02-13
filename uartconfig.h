/*
 * uartconfig.h
 *  Author: mo
 * Created: 10/02/2020 08:02:57 م
 */
#ifndef UARTCONFIG_H_
#define UARTCONFIG_H_
/*UCSRB*/
#define TXB8    0
#define RXB8    1
#define UCSZ2   2
#define TXEN    3
#define RXEN    4
#define UDRIE   5
#define TXCIE   6
#define RXCIE   7
/*UCSRC*/
/*URSEL UMSEL UPM1 UPM0 USBS UCSZ1 UCSZ0 UCPOL UCSRC*/
#define UCPOL    0
#define UCSZ0    1
#define UCSZ1    2
#define USBS     3
#define UPM0     4
#define UPM1     5
#define UMSEL    6
#define URSEL    7
/*UCSRA*/
/*RXC TXC UDRE FE DOR PE U2X MPCM */
#define MPCM    0
#define U2X     1
#define UPE     2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

typedef enum En_BAUD_Rate{
Baud9600=103,
Baud14400=0x44,
Baud19200=0x33,
Baud38400=0x19/*
Baud57600=0x10,
Baud115200=0x08,
Baud2400=0x01A0,
*/
}En_BAUD_Rate;
typedef enum En_Stop_config{
OneStopBit,
TwoStopBits
}En_Stop_config;
typedef enum EN_Parity{
NoParity,
EvenParity,
OddParity

}EN_Parity;

typedef enum EN_Data_Size{
FiveBits,
SexBits,
SevenBits,
EightBits,
NineBits

}EN_Data_Size;
typedef enum EN_UartMode{
ASynchronous,
Synchronous,
/*full_duplexinterrupt,
transmitInterrupt,
recieveInterrupt,
transmitPooling,
recievePooling,
full_duplexPooling
*/
}EN_UartMode;
#endif /* UARTCONFIG_H_ */
