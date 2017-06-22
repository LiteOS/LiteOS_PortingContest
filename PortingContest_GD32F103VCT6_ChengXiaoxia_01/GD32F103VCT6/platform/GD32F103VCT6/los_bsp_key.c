#include "los_bsp_key.h"
#include "gd32f10x.h"
/******************************************************************************
    here include some special hearder file you need
******************************************************************************/




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
    GPIO_InitPara GPIO_InitStructure;
    RCC_APB2PeriphClock_Enable(RCC_APB2PERIPH_GPIOB ,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    return ;
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
    unsigned int KeyVal = 0xFF;
    
    //add you code here.
    if( GPIO_ReadInputBit( GPIOB , GPIO_PIN_14 ) == 0 )
		{
			KeyVal = 0;
		}
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



