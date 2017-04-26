#include "los_bsp_led.h"

/******************************************************************************
	here include some special hearder file you need
******************************************************************************/
#include "board.h"
#include "fsl_port.h"
#include "fsl_clock.h"

/*****************************************************************************
 Function    : LOS_EvbLedInit
 Description : Init LED device
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbLedInit(void)
{
    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortB);

    PORT_SetPinMux(PORTA, 19u, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTA, 18u, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, 0u, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, 1u, kPORT_MuxAsGpio);

    gpio_pin_config_t config =
    {
        kGPIO_DigitalOutput,
        0,
    };
    GPIO_PinInit(GPIOA, 19u, &config);
    GPIO_PinInit(GPIOA, 18u, &config);		
    GPIO_PinInit(GPIOB, 0u, &config);		
    GPIO_PinInit(GPIOC, 1u, &config);

    GPIO_WritePinOutput(GPIOB, LED3_B0, 1);
    GPIO_WritePinOutput(GPIOA, LED_GREEN_A19, 1);
    GPIO_WritePinOutput(GPIOA, LED_BLUE_A18 , 1);
    GPIO_WritePinOutput(GPIOC, LED_RED_C1, 1);
    return ;
}

/*************************************************************************************************
 *  Function    £ºLOS_EvbLedControl
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
                GPIO_WritePinOutput(GPIOB, LED3_B0, 0);
            }
            else
            {
                //add you code here.
                /*led1 off */
                GPIO_WritePinOutput(GPIOB, LED3_B0, 1);
            }
            break;
        }
        case LOS_LED2:
        {
            if (cmd == LED_ON)
            {
                //add you code here.
                /*led2 on */
            }
            else
            {
                /*led2 off */
            }
            break;
        }
        case LOS_LED3:
        {
            if (cmd == LED_ON)
            {
                      /*led3 on */
            }
            else
            {
                     /*led3 off */
            }
            break;
        }
        default:
        {
            break;
        }
    }
	return ;
}


