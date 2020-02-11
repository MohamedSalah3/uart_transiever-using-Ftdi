/*Timer.c*/
#include "led.h"
#include "ledConfig.h"
#include "timers.h"
#include "registers.h"
#include "Interrupts.h"
uint8_t volatile status_Flag=1;
uint8_t Prescaler_Value=0;
uint8_t pooling=0;
uint8_t pooling_2=0;
uint8_t Prescaler_Value2=0;
uint8_t u8g_T1_Prescaler=0;
volatile uint8_t pwm_time_on=0,flag=0;

void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal,uint8_t u8_initialValue, uint8_t u8_outputCompare,En_timer0Interrupt_t en_interruptMask)
{
if(en_prescal == T0_NO_CLOCK)
{/*
if there is no clock the timer will be disabled
*/
timer0Stop();
}
else
{
TCCR0 |= en_mode|en_prescal;
Prescaler_Value=en_prescal;
TCNT0 = u8_initialValue;
switch(en_OC0){
	case  T0_OC0_DIS:
	{
	TCCR0 &= 0xCF;
		break;
	}
	case T0_OC0_TOGGLE:
	{
		TCCR0|=T0_OC0_TOGGLE;
		break;
	}
	case  T0_OC0_CLEAR:
	{
	TCCR0 |= T0_OC0_CLEAR;

		break;
	}
	case T0_OC0_SET:
	{
		TCCR0 |=T0_OC0_SET;
		break;
	}

}
OCR0  =u8_outputCompare;
switch(en_interruptMask){
case  T0_POLLING:{
pooling=0;
G_interrupt_Disable();
TIMSK &= T0_POLLING;
break;
}
case T0_INTERRUPT_NORMAL :
{pooling=1;
G_interrupt_Enable();
TIMSK |= T0_INTERRUPT_NORMAL;
break;
}
case T0_INTERRUPT_CMP:
{pooling=1;
//G_interrupt_Enable();
SET_BIT(SREG,7);
TIMSK |= T0_INTERRUPT_NORMAL;
TIMSK |=T0_INTERRUPT_CMP;
break;
}
}

}

}
void timer0Set(uint8_t u8_value)
{
TCNT0 =	u8_value;
}

uint8_t timer0Read(void)
{
	 return TCNT0;
}

/*
REStart the clocck by  cs00 cs01 cs02
						0     0    0
						Then
						cs00 cs01 cs02
Depending on prescaler	x     X    X

*/
void timer0Start(void)
{
	 TCCR0 &= (0xF8);
	 TCCR0 |= Prescaler_Value;
}
/*	choosing no clock source cs00 cs01 cs02
						      0     0    0
*/
void timer0Stop(void)
 {

TCCR0 &= (0xF8);

 }
 /*



 */
 void timer0DelayMs(uint16_t u16_delay_in_ms)
 {
	uint32_t u32_loop=0;
/*	u32_ovf_counter=0;
		timer0Set(48);
		while(u32_ovf_counter <= (64)*u16_delay_in_ms);
*/
for (u32_loop=0;u32_loop<u16_delay_in_ms;u32_loop++)
{
	while ((TIFR&0x01)==0);
	TIFR |=0x01;

}

}
 /*
 at pooling _no prescaling
 240at TCNT0

 */
 void timer0DelayUs(uint32_t u32_delay_in_us)
 {  uint32_t u32_loop=0;
	for (u32_loop=0;u32_loop<u32_delay_in_us;u32_loop++)
	{
	timer0Set(240);
	while(timer0Read()<=255);
	//while(u32_ovf_counter <= (8*u32_delay_in_us/1000));
	}
	TIFR |=(1<<TOV0);/*Clear the flag*/
}/*1*/
void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency)
{
float dutyReal;
pwm_time_on=MAX_HOLD;
dutyReal=((float)u8_dutyCycle/(float)FULL_SPEED);
pwm_time_on=(float)pwm_time_on*dutyReal;
switch(pooling)
{
	case 0:
	{
	timer0Start();
	timer0Set(pwm_time_on);
	//freq 50KHZ is the Max frequency possible
	while ((TIFR&0x01)==0);
	TIFR |=0x01;
	PORTC_DATA |=0xff;
	timer0Start();
	timer0Set(MAX_HOLD-pwm_time_on);
	//freq
	while ((TIFR & 0x01)==0);
	TIFR |=0x01;
	PORTC_DATA &=0x00;

break;
}
case 1:
{
timer0Start();
OCR0=pwm_time_on;
break;
}

}

}





void Timer_interrupt_COMP_routine(void)
{
	PORTD_DATA ^=0xff;

}


/*
 * Description:
 * @param:
 */
void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,
	En_timer1perscaler_t en_prescal,uint16_t u16_initialValue,
	uint16_t u16_outputCompareA,uint16_t u16_outputCompareB,
	 uint16_t u16_inputCapture,En_timer1Interrupt_t en_interruptMask)
 {
	TCCR1 |= en_mode | en_OC;
	u8g_T1_Prescaler=en_prescal;
	OCR1A =u16_outputCompareA;
	OCR1B =u16_outputCompareB;
	TCNT1=u16_initialValue;
	switch(en_interruptMask)
	{
		case T1_POLLING:
		{
			TIMSK &=0xC3;

			/*	     OCIE0 ToIE0   ALL INTERRUPT T1    	OCIE0 ToIE0
			TIMSK &=  1     1        0 0 0 0 	           1     1
			All T1 Interrupts enable are cleared
			but other timers interrupt enable are not effected
			*/
		break;
		}
		case T1_INTERRUPT_NORMAL:
		{
			TIMSK |=T1_INTERRUPT_NORMAL;
		break;
		}
		case T1_INTERRUPT_CMP_1A:
		{
			TIMSK |=T1_INTERRUPT_CMP_1A;
			break;
		}
		case T1_INTERRUPT_CMP_1B:
		{
			TIMSK |=T1_INTERRUPT_CMP_1B;
			break;
		}
		case T1_INTERRUPT_ICAPTURE:
		{
			TIMSK |=T1_INTERRUPT_ICAPTURE;
			break;
		}
		case T1_INTERRUPT_All:
		{
			TIMSK|=T1_INTERRUPT_All;
		/*Enables all interrupst for Timer1*/
		break;
		}

	}




	}


void timer1Set(uint16_t u16_value)
{
TCNT1=u16_value;
}

/**
 * Description:
 * @return TCNT1
 */
uint16_t timer1Read(void)
{
return TCNT1;
}

/**
 * Description:
 * @param
 */
void timer1Start(void)
{
TCCR1|=u8g_T1_Prescaler;
}

/**
 * Description:
 * @param
 */
void timer1Stop(void)
{
TCCR1 &=0xfff8;
/*Keep all sittings as it is and put zeros in cs10,cs11,cs12*/
}

/**
 * Description:
 * @param delay
 */
void timer1DelayMs(uint16_t u16_delay_in_ms)
{


}

/*
 * Description:
 * user defined
 */
void timer1DelayUs(uint32_t u32_delay_in_us)
{


}

/**
 * Description:
 * @param dutyCycle
 */
void timer1SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency)
{


}

void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal2, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask)
{
if(en_prescal2 == T2_NO_CLOCK)
{/*
if there is no clock the timer will be disabled
*/
timer2Stop();
}
else
{
TCCR2 |= en_mode|en_prescal2 ;
Prescaler_Value2=en_prescal2;
TCNT2 = u8_initialValue;
switch(en_OC){
	case  T2_OC2_DIS:
	{
	TCCR2 &= 0xCF;
		break;
	}
	case T2_OC2_TOGGLE:
	{
		TCCR2 |=T2_OC2_TOGGLE;
		break;
	}
	case  T2_OC2_CLEAR:
	{
	TCCR2 |= T2_OC2_CLEAR;

		break;
	}
	case T2_OC2_SET:
	{
		TCCR2 |=T2_OC2_SET;
		break;
	}

}
OCR2  =u8_outputCompare;
switch(en_interruptMask){
case  T2_POLLING:
pooling_2=0;
G_interrupt_Disable();
TIMSK &= T2_POLLING;
break;
case T2_INTERRUPT_NORMAL :
{
	pooling_2=1;
G_interrupt_Enable();
TIMSK |= T2_INTERRUPT_NORMAL;
break;
}
case T2_INTERRUPT_CMP:
{
	pooling_2=1;
G_interrupt_Enable();
//SET_BIT(SREG,7);
TIMSK |=T2_INTERRUPT_NORMAL;
TIMSK |=T2_INTERRUPT_CMP;
break;
}
}

}



}
/**
* Description:
* @param value
*/
void timer2Set(uint8_t u8_a_value)
{
TCNT2=u8_a_value;
}

/**
* Description:
* @return
*/
uint8_t timer2Read(void){
return TCNT2;
}

/**
* Description:
*/
void timer2Start(void)
{
TCCR2 &= 0xf8;
TCCR2 |= Prescaler_Value2;
}

/**
* Description:
*/
void timer2Stop(void)
{
TCCR2 &= 0xf8;

}

/**
* Description:pooline No interrupt
* @param delay
*	switch(Prescaler_Value2)
		{
		case no:
		Prescalercounst=58;
		break;
		case 8:
		Prescalercounst=8;
		break;
		case 32:
		Prescalercounst=2;
		break;
		case 64:
		Prescalercounst=1;
		break;
		case 128:
		Prescalercounst=1;
		break;
		case 256:
		Prescalercounst=1;
		break;
		case 256:
		Prescalercounst=1;
		break;

		}*/
void timer2DelayMs(uint16_t u16_delay_in_ms)
{
	volatile uint16_t count=0;
	volatile uint8_t Prescalercounst=0,set_timer2=0;
	switch(Prescaler_Value2)
	{
		case T2_PRESCALER_NO:{
		Prescalercounst=58;
		set_timer2=10;
		break;}
		case T2_PRESCALER_8:
		{Prescalercounst=8;
		set_timer2=12;
		break;}
		case T2_PRESCALER_32:
		{Prescalercounst=2;
		set_timer2=8;
		break;}
		case T2_PRESCALER_64:
		{Prescalercounst=1;
		set_timer2=6;
		break;}
		case T2_PRESCALER_128:
		{Prescalercounst=1;
		set_timer2=131;
		break;}
		case T2_PRESCALER_256:
		{Prescalercounst=1;
		set_timer2=194;
		break;}
		case T2_PRESCALER_1024:
		{Prescalercounst=1;
		set_timer2=240;
		break;}
	}
	for (count=0;count<(u16_delay_in_ms*Prescalercounst);count++)
	{
		timer2Set(set_timer2);//10 for no prescaler....12 for 8 prescaler .... 8 for 32 prescaler ....6 for prescaler 64 .....
		//131 for 128 prescaler.......194 for 256 prescaler....240 for 1024
		while ((TIFR & 0x40)==0);
		TIFR |=0x40;

	}
}

/*Always No prescaler...pooling ...timer2Set(240)*/
void timer2DelayUs(uint32_t u16_delay_in_us)
{
	volatile uint16_t count =0;
	for (count=0;count<u16_delay_in_us;count++)
	{
		timer2Set(254);//254 for no prescaler
		while ((TIFR & 0x40)==0);
		TIFR |=0x40;

	}

}

/**
* Description:
* @param dutyCycle
*/
void timer2SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency)
{

float dutyReal;
pwm_time_on=MAX_HOLD;
dutyReal=((float)u8_dutyCycle/(float)FULL_SPEED);
pwm_time_on=(float)pwm_time_on*dutyReal;
switch(pooling_2)
{
	case 0:
	{
		timer2Start();
		timer2Set(pwm_time_on);
		//freq 50KHZ is the Max frequency possible
		while ((TIFR&0x04)==0);
		TIFR |=0x04;
		PORTC_DATA |=0xff;
		timer2Start();
		timer2Set(MAX_HOLD-pwm_time_on);
		//freq
		while ((TIFR & 0x04)==0);
		TIFR |=0x04;
		PORTC_DATA &=0x00;

		break;
	}
	case 1:
	{
		timer2Start();
		OCR2=pwm_time_on;
		break;
	}

}


}


void Timer2_interrupt_COMP_routine(void)
{



}
void Timer2_interrupt_routine(void)
{


}
