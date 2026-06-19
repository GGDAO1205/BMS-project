#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

typedef enum
{
    LED1,
    LED2
} LED_NumTypeDef;

typedef enum
{
    OFF = 1,
    ON  = 0
} LED_StateTypeDef;

void LED_Init(void);
void LED_Set(LED_NumTypeDef led, LED_StateTypeDef state);
void LED1_Turn(void);
void LED2_Turn(void);

#endif


