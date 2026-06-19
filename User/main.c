#include "stm32f10x.h"                  // Device header
#include "Delay.h"                      //系统延时函数声明
#include "Oled.h"
#include "Timer.h"


uint16_t Num;
int main(void)
{
	// 全局中断分组，整个程序仅调用一次
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置 Cortex-M3/M4 内核的中断优先级分组规则（几位抢占几位响应）
	
	Timer_Init();
	OLED_Init();
	OLED_ShowString(1,1,"Num:");
	OLED_ShowString(2,1,"CNT:");
//	OLED_ShowChar(1,1,'I');
//	Delay_ms(1000);
//	OLED_Clear();
//	OLED_ShowString(1,1,"MISS");
//	Delay_ms(1000);
//	OLED_Clear();
//	OLED_ShowString(1,1,"YOU");
//	Delay_ms(1000);
//	OLED_Clear();
//	OLED_ShowString(1,1,"I MISS YOU");
	
    while(1)
    {
		
		OLED_ShowNum(1,5,Num,5);
		OLED_ShowNum(2,5,Timer_GetCounter(),5);
				
	}
}

