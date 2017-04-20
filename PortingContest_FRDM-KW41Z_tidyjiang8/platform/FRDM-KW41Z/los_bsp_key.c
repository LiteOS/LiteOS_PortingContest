#include "los_bsp_key.h"

/******************************************************************************
	here include some special hearder file you need
******************************************************************************/
#include "board.h"
#include "fsl_port.h"
#include "fsl_clock.h"
//#include "fsl_debug_console.h"




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
	PORT_SetPinMux(PORTC, 5u, kPORT_MuxAsGpio);

	gpio_pin_config_t config =
 	{
  		kGPIO_DigitalInput,
   		0,
 	};
	GPIO_PinInit(GPIOC, 5u, &config);
	
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
	unsigned int KeyVal = 0xFFFFFFFF; 
	
	//add you code here.
	KeyVal = GPIO_ReadPinInput(GPIOC, KeyNum);
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


