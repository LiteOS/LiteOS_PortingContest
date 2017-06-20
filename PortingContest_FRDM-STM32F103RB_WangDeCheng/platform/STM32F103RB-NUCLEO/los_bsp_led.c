#include "los_bsp_led.h"
#include "stm32f10x.h"
/******************************************************************************
    here include some special hearder file you need
******************************************************************************/



/*****************************************************************************
 Function    : LOS_EvbLedInit
 Description : Init LED device
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbLedInit(void)
{
    //add you code here.
    /*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

		/* 关闭所有led灯	*/
		GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
		
		/* 关闭所有led灯	*/
		GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);	 
    
    /* 关闭所有led灯	*/
		GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
    return ;
}

/*************************************************************************************************
 *  Function    ：LOS_EvbLedControl
 *  Discription : Led control function
 *  Input       : (1) index Led's index                                                                  *
 *                (2) cmd   Led on or off  
 *  Output      : None
 *  Return      : None                                                                                *
 *                                                                                 *
**************************************************************************************************/
void LOS_EvbLedControl(int index, int cmd)
{
    switch (index)
    {
    case LOS_LED1:
    {
        if (cmd == LED_ON)
        {
            //add you code here.
            /*led1 on */
            GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
        }
        else
        {
            //add you code here.
            /*led1 off */
            GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
        }
        break;
    }
    case LOS_LED2:
    {
        if (cmd == LED_ON)
        {
            //add you code here.
            /*led2 on */
            GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
        }
        else
        {
            //add you code here.
            /*led2 off */
            GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
        }
        break;
    }
    case LOS_LED3:
    {
        if (cmd == LED_ON)
        {
            //add you code here.
            /*led3 on */
            GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
        }
        else
        {
            //add you code here.
            /*led3 off */
            GPIO_ResetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return;
}


