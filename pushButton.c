/*
 * pushButton.c
 *
 * Created: 17/01/2020 05:27:05 pm
 *  Author: mo
 */
#include "timers.h"
 #include "pushButton.h"
 #include "pushButtonConfig.h"
 #include "led.h"
 //#include "SwICU.h"
extern uint8_t icu_started;
/*
#define BTN_0_GPIO	GPIOC
#define BTN_0_BIT	BIT4

#define BTN_1_GPIO	GPIOB
#define BTN_1_BIT	BIT2

#define BTN_2_GPIO	GPIOA
#define BTN_2_BIT	BIT2

#define BTN_3_GPIO 	GPIOA
#define BTN_3_BIT	BIT3
BTN_0,
	BTN_1,
	BTN_2,
	BTN_3
*/
extern uint8_t volatile status_Flag;
void pushButtonInit(En_buttonId_t en_butotn_id)
{

switch(en_butotn_id)
{
case BTN_0:
{
gpioPinDirection(BTN_0_GPIO,BTN_0_BIT,LOW);

break;
}
case BTN_1:
{
gpioPinDirection(BTN_1_GPIO,BTN_1_BIT,LOW);

break;
}
case BTN_2:
{
gpioPinDirection(BTN_2_GPIO,BTN_2_BIT,LOW);

break;
}
case BTN_3:
{
gpioPinDirection(BTN_3_GPIO,BTN_3_BIT,LOW);

break;
}
}
}

En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_butotn_id)
{

switch(en_butotn_id)
{
case BTN_0:
{
if(gpioPinRead(BTN_0_GPIO,BTN_0_BIT) == Pressed)
{ timer0DelayMs(50);
	if(gpioPinRead(BTN_0_GPIO,BTN_0_BIT) == Pressed)
	return Pressed;
	else {return Released;}
}else{return Released;}
break;
}
case BTN_1:
{
if(gpioPinRead(BTN_1_GPIO,BTN_1_BIT) == Pressed)
{
timer0DelayMs(50);
if(gpioPinRead(BTN_1_GPIO,BTN_1_BIT) == Pressed)
return Pressed;
	else {return Released;}
}else{return Released;}
break;
}
case BTN_2:
{
if(gpioPinRead(BTN_2_GPIO,BTN_2_BIT) == Pressed)
{
	timer0DelayMs(50);
	if(gpioPinRead(BTN_2_GPIO,BTN_2_BIT) == Pressed)
	return Pressed;
else {return Released;}
}else{return Released;}
break;
}
case BTN_3:
{
if(gpioPinRead(BTN_3_GPIO,BTN_3_BIT) == Pressed)
{
	timer0DelayMs(50);
	if(gpioPinRead(BTN_3_GPIO,BTN_3_BIT) == Pressed)
	return Pressed;
else {return Released;}
}else{return Released;}
break;
}

}
}

