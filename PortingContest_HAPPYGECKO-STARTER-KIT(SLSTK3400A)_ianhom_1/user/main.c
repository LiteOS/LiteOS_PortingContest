#include "los_sys.h"
#include "los_tick.h"
#include "los_task.ph"
#include "los_config.h"

#include "los_bsp_led.h"
#include "los_bsp_key.h"
#include "los_bsp_uart.h"
#include "los_inspect_entry.h"
#include "los_demo_entry.h"

#include <string.h>

#ifdef EFM32HG322F64
#include "cslib.h"
#include "comm_routines.h"
#include "device_init.h"
#endif

extern void LOS_EvbSetup(void);


/*****************************************************************************
 Function    : HAL_init
 Description : Init for HAL
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void HAL_init(void)
{
    systemInit();
    CSLIB_initHardware();
    CSLIB_initLibrary();
    return;
}


/*****************************************************************************
 Function    : main
 Description : Main function entry
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT
int main(void)
{
    UINT32 uwRet;

    HAL_init();

    /*Init LiteOS kernel */
    uwRet = LOS_KernelInit();
    if (uwRet != LOS_OK) {
        return LOS_NOK;
    }
    /* Enable LiteOS system tick interrupt */
    LOS_EnableTick();

    /* Init the device on the dev board */
    LOS_EvbSetup(); 

    /* init the device on the dev board */
    LOS_Inspect_Entry();

    /* Kernel start to run */
    LOS_Start();
    for (;;);
    /* Replace the dots (...) with your own code.  */
}

/* End of file */

