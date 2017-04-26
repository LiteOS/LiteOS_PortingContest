#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "los_bsp_uart.h"
#include "los_demo_debug.h"

/******************************************************************************
	here include some special hearder file you need
******************************************************************************/
#include "board.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "fsl_lpuart.h"

/*****************************************************************************
 Function    : LOS_EvbUartInit
 Description : Init uart device
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbUartInit(void)
{
    /* Initialize LPUART0 pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortC);

    PORT_SetPinMux(LPUART_DEBUG_PORT, LPUART_DEBUG_RX_PIN, kPORT_MuxAlt4);
    PORT_SetPinMux(LPUART_DEBUG_PORT, LPUART_DEBUG_TX_PIN, kPORT_MuxAlt4);

    BOARD_BootClockRUN();

    /* SIM_SOPT2[27:26]:
     *  00: Clock Disabled
     *  01: MCGFLLCLK
     *  10: OSCERCLK
     *  11: MCGIRCCLK
     */
    CLOCK_SetLpuartClock(2);
    //	lpuart_config_t lpuart_config;
    //LPUART_GetDefaultConfig(&lpuart_config);
    //lpuart_config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    /* Enable clock and initial UART module follow user configure structure. */
    //LPUART_Init(LPUART0, &lpuart_config, BOARD_DEBUG_UART_CLK_FREQ);
    //LPUART_EnableTx(LPUART0, true);
    //LPUART_EnableRx(LPUART0, true);
    DbgConsole_Init(BOARD_DEBUG_UART_BASEADDR, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, BOARD_DEBUG_UART_CLK_FREQ);

    return;
}

/*****************************************************************************
 Function    : LOS_EvbUartWriteByte
 Description : Uart write one byte
 Input       : const char c
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbUartWriteByte(const char c)
{
    LPUART_WriteBlocking(LPUART0, (const uint8_t *)&c, 1);
    return;
}

/*****************************************************************************
 Function    : LOS_EvbUartReadByte
 Description : Uart reaad one byte
 Input       : char* c
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbUartReadByte(char* c)
{
    LPUART_WriteBlocking(LPUART0, c, 1);
    return;
}

static char _buffer[128];

/*****************************************************************************
 Function    : LosUartPrintf
 Description : Los printf function
 Input       : char* fmt, ...
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbUartPrintf(char* fmt, ...)
{
    int i;
    va_list ap;
    va_start(ap, fmt);
    vsprintf(_buffer, fmt, ap);
    va_end(ap);

    for (i = 0; _buffer[i] != '\0'; i++)
    {
        LOS_EvbUartWriteByte(_buffer[i]);
    }

    return;
}

/*****************************************************************************
 Function    : LOS_EvbUartWriteStr
 Description : Uart Write String function
 Input       : const char* str
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbUartWriteStr(const char* str)
{
    while(*str) {
        LOS_EvbUartWriteByte(*str);
        str++;
    }

    return;
}

#ifndef LOS_KERNEL_TEST_KEIL_SWSIMU
///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch/*, FILE *f*/)
{
    /* 发送一个字节数据到串口USART */
    LOS_EvbUartWriteByte((char)ch);
    
    return (ch);
}
#endif
