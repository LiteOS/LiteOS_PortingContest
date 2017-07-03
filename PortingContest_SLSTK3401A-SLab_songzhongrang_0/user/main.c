#include "los_sys.h"
#include "los_tick.h"
#include "los_task.ph"
#include "los_config.h"

#include "los_bsp_led.h"
#include "los_bsp_key.h"
#include "los_bsp_uart.h"

#ifdef EFM32PG1B200F256GM48
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "bsp.h"
#endif

#include "los_inspect_entry.h"

#include <string.h>

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

    UINT32 uwRet;

#ifdef EFM32PG1B200F256GM48
	UINT32 freq;
	EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_STK_DEFAULT;
	CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_STK_DEFAULT;
	
	/* Chip errata */
	CHIP_Init();

	/* Init DCDC regulator and HFXO with kit specific parameters */
	EMU_DCDCInit(&dcdcInit);
	CMU_HFXOInit(&hfxoInit);

	/* Switch HFCLK to HFXO and disable HFRCO */
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
	CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);

	freq = CMU_ClockFreqGet(cmuClock_CORE);

#endif
	
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
    
#ifdef EFM32PG1B200F256GM48
	printf("freq is %ld\n", freq);
#endif

    LOS_Inspect_Entry();
		
    /* Kernel start to run */
    LOS_Start();
    for (;;);
    /* Replace the dots (...) with your own code.  */
}
