#include "los_sys.h"
#include "los_tick.h"
#include "los_task.ph"
#include "los_config.h"

#include "los_bsp_led.h"
#include "los_bsp_key.h"
#include "los_bsp_uart.h"

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "bsp.h"

#include "los_inspect_entry.h"

#include <string.h>

#include "display.h"
#include "textdisplay.h"
#include "retargettextdisplay.h"
static DISPLAY_Device_t displayDevice;


extern void LOS_EvbSetup(void);

static UINT32 g_uwboadTaskID;
LITE_OS_SEC_TEXT VOID LOS_BoadExampleTskfunc(VOID)
{
    while (1)
    {
        LOS_EvbLedControl(LOS_LED2, LED_ON);
        LOS_EvbUartWriteStr("Board Test\n");
        LOS_TaskDelay(500);
        LOS_EvbLedControl(LOS_LED2, LED_OFF);
        LOS_TaskDelay(500);
    }
}
void LOS_BoadExampleEntry(void)
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stTaskInitParam;

    (VOID)memset((void *)(&stTaskInitParam), 0, sizeof(TSK_INIT_PARAM_S));
    stTaskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LOS_BoadExampleTskfunc;
    stTaskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE;
    stTaskInitParam.pcName = "BoardDemo";
    stTaskInitParam.usTaskPrio = 10;
    uwRet = LOS_TaskCreate(&g_uwboadTaskID, &stTaskInitParam);

    if (uwRet != LOS_OK)
    {
        return ;
    }
    return ;
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

#if 1
    UINT32 uwRet;

	/* Chip errata */
	CHIP_Init();
	
	/*Init LiteOS kernel */
    uwRet = LOS_KernelInit();
    if (uwRet != LOS_OK) {
        return LOS_NOK;
    }
	/* Enable LiteOS system tick interrupt */
    LOS_EnableTick();
	
    /* 
        Notice: add your code here
        here you can create task for your function 
        do some hw init that need after systemtick init
    */
    LOS_EvbSetup();
    //LOS_BoadExampleEntry();

#if 0
	printf( "\n\n Welcome"
			"\n\n Lite OS"
			"\n\n ");
#endif

    LOS_Inspect_Entry();
		
    /* Kernel start to run */
    LOS_Start();
    for (;;);
    /* Replace the dots (...) with your own code.  */
#else
	CHIP_Init();

        		/* Initialize LCD driver */
		DISPLAY_Init();

		/* Retrieve the properties of the display. */
		if (DISPLAY_DeviceGet( 0, &displayDevice ) != DISPLAY_EMSTATUS_OK)
		{
		  /* Unable to get display handle. */
		  while (1);
		}

		/* Retarget stdio to the display. */
		if (TEXTDISPLAY_EMSTATUS_OK != RETARGET_TextDisplayInit())
		{
		  /* Text display initialization failed. */
		  while (1);
		}

		if (TEXTDISPLAY_EMSTATUS_OK == RETARGET_WriteString( "\n\n Welcome"
			"\n\n Lite OS"
			"\n\n ")) {
			printf("sss\n");
		} else {
			printf("err\n");
		}
                
	//LOS_EvbLcdInit();

	for (;;);
	
#endif
}
