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
//#include "fsl_debug_console.h"


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
	/* Affects PORTC_PCR6 register */
	PORT_SetPinMux(PORTC, 6u, kPORT_MuxAlt4);
	/* Affects PORTC_PCR7 register */
	PORT_SetPinMux(PORTC, 7u, kPORT_MuxAlt4);
        
        BOARD_BootClockRUN();
        
        /* SIM_SOPT2[27:26]:
        *  00: Clock Disabled
        *  01: MCGFLLCLK
        *  10: OSCERCLK
        *  11: MCGIRCCLK
        */
        CLOCK_SetLpuartClock(2);
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
	//add you code here.
        LPUART_WriteBlocking(LPUART0, &c, 1);
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
	//add you code here.
        
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
	//add you code here.
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
	//add you code here.
        while(*str) {
            LOS_EvbUartWriteByte(*str);
            str++;
        }
	//DbgConsole_Printf(str);
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
