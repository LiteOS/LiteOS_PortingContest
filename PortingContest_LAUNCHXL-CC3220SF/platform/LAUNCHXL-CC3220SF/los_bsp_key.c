#include "los_bsp_key.h"

#ifdef LAUNCHXL_CC3220SF

#endif

/*****************************************************************************
 Function    : LOS_EvbKeyInit
 Description : Init keys
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbKeyInit(void)
{
#ifdef LAUNCHXL_CC3220SF
    *((volatile unsigned long *)(0x44025060))  = 0x01;       /* Enable gpio2 clock */
	  *((volatile unsigned long *)(0x40006400)) &= ~0x40;   /* input */
    *((volatile unsigned long *)(0x4402E0F8)) = 0x00;	
#endif

    return ;
}


/*****************************************************************************
 Function    : LOS_EvbGetKeyVal
 Description : Get key value
 Input       : KeyNum
 Output      : None
 Return      : None
 *****************************************************************************/
uint8_t LOS_EvbGetKeyVal(int KeyNum)
{
#ifdef LAUNCHXL_CC3220SF
    switch(KeyNum) {
        case 0:
		    case 1:
            return !(*((volatile unsigned long *)(0x400063FC)) & 0x40);
        default:
            break;
    }
#endif
    return LOS_GPIO_ERR;

}

/* End of file */

