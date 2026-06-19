#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启tim2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0111);
	//TIM_InternalClockConfig(TIM2);//为时钟基准单元选择时钟源(上电默认内部时钟源这行可省略)
	
	GPIO_InitTypeDef GPIO_Initstructrue;
	GPIO_Initstructrue.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstructrue.GPIO_Pin = GPIO_Pin_0;
	GPIO_Initstructrue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructrue);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;//对定时器基准时钟分频，调整采样 / 死区等外设单元的时钟频率，不改变计数器本身的计数频率。
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//定时器向上计数
	TIM_TimeBaseStruct.TIM_Period = 10 - 1;//自动重装载值 ARR，计数器计到此值后溢出
	TIM_TimeBaseStruct.TIM_Prescaler = 1 - 1;//PSC预分频器的值（可改变计数器计数频率）
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;//通用定时器没有该寄存器，此参数无效，固定填 0
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);//初始化时基单元
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//由于时基单元初始化之后会立刻产生一次更新事件，手动清除事件标志让定时器从0开始计数
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//开启TIM2指定中断源，此处指定了TIM2的中断源为更新中断，可根据实际功能需求选择对应中断源
	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//选择定时器TIM2的中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//开启/关闭NVIC中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC
	
	TIM_Cmd(TIM2,ENABLE);//启动TIM2
}

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
}

void TIM2_IRQHandler(void)//TIM2_IRQHandler 是内核约定的固定入口，必须和向量表一致，不能改
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//通过判断中断标志位来检查是否触发了更新中断
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//先清除中断标志挂起位
		
		Num++;
	}
}


