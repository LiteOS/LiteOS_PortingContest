#include "sam.h"
#include "los_bsp_uart.h"
#include "uart.h"
#include "Board_LED.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

extern void UART_Configure(Uart *uart,
					uint32_t mode,
					uint32_t baudrate,
					uint32_t masterClock);

extern uint8_t UART_GetChar(Uart *uart);
extern void UART_PutChar(Uart *uart, uint8_t c);

void Error_Handler(void)
{
  /* Turn LED4 on */
  LED_On(0);
  while(1)
  {
  }
}


void LOS_EvbUartInit(void)
{
	UART_Configure(UART0,4,115200,30000000);
	return ;
}


/*************************************************************************************************
 *  功能：向串口1发送一个字符                                                                    *
 *  参数：(1) 需要被发送的字符                                                                   *
 *  返回：                                                                                       *
 *  说明：                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartWriteByte(char c)
{
	UART_PutChar(UART0, c);
	return ;
}

/*************************************************************************************************
 *  功能：向串口1发送一个字符串                                                                  *
 *  参数：(1) 需要被发送的字符串                                                                 *
 *  返回：                                                                                       *
 *  说明：                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartWriteStr(const char* str)
{
    while (*str)
    {
			UART_PutChar(UART0, *str++);
    }
	return ;
}


/*************************************************************************************************
 *  功能：从串口1接收一个字符                                                                    *
 *  参数：(1) 存储接收到的字符                                                                   *
 *  返回：                                                                                       *
 *  说明：                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartReadByte(char* c)
{
	UART_GetChar(UART0);
	return ;
}


static char _buffer[256];
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
	return ;
}

int fputc(int ch, FILE *f)
{
	LOS_EvbUartWriteByte(ch);
	return (ch);
}

