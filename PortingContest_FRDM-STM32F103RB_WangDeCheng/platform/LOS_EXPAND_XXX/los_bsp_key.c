#include "los_bsp_key.h"
#include "los_typedef.h"
#include "stm32f10x.h"
/******************************************************************************
    here include some special hearder file you need
******************************************************************************/

/* 定义按键连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
// KEY1
#define KEY1_GPIO_PORT    	GPIOC			            /* GPIO端口 */
#define KEY1_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define KEY1_GPIO_PIN				GPIO_Pin_13			        /* 连接到SCL时钟线的GPIO */



/*****************************************************************************
 Function    : LOS_EvbKeyInit
 Description : Init GIOP Key 
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbKeyInit(void)
{
    //add you code here.
    //BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
    GPIO_InitTypeDef GPIO_InitStructure;
 
		RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);//使能PORTA,PORTE时钟

		GPIO_InitStructure.GPIO_Pin  =KEY1_GPIO_PIN;//KEY0-KEY2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
		GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);//初始化GPIOE2,3,4

    return;
}

/*****************************************************************************
 Function    : LOS_EvbGetKeyVal
 Description : Get GIOP Key value
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
unsigned int LOS_EvbGetKeyVal(int KeyNum)
{
    UINT32 KeyVal = 0xFFFFFFFF;
    
    //add you code here.
    if(KeyNum > 1)
    {
        return 0xFF;
    }
    KeyVal = (UINT32)GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PIN);
    return KeyVal;
}

/*****************************************************************************
 Function    : EXTIxxx_IRQHandler
 Description : EXT xxx IRQ Handler detail,change the function name 
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void EXTIxxx_IRQHandler(void)
{
    //add you code here.
    
    return;
}



