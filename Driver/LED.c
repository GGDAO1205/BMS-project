#include "LED.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    LED_Set(LED1, OFF);
    LED_Set(LED2, OFF);
}

//用于控制LED1和LED2的亮灭
//led：取值为LED1、LED2,可在@LED_NumTypeDef中看到
//state：取值为ON、OFF,可在@LED_StateTypeDef中看到
void LED_Set(LED_NumTypeDef led, LED_StateTypeDef state)
{
    switch(led)
    {
        case LED1:
            if(state == ON)
                GPIO_ResetBits(GPIOA, GPIO_Pin_1);
            else
                GPIO_SetBits(GPIOA, GPIO_Pin_1);
            break;

        case LED2:
            if(state == ON)
                GPIO_ResetBits(GPIOA, GPIO_Pin_2);
            else
                GPIO_SetBits(GPIOA, GPIO_Pin_2);
            break;
        
    }
}

 void LED1_Turn(void)
 {
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
 }

 void LED2_Turn(void)
 {
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
 }
 
 
 
 