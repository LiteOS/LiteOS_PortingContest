#include "sam.h"
#include "los_bsp_uart.h"
#include "Board_LED.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "los_demo_debug.h"

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
	uint32_t ul_sr;
	PMC->PMC_WPMR = 0x504D4300;             /* Disable write protect            */
	PMC->PMC_PCER0 = ((1UL << ID_PIOA ) | (1UL << ID_UART0));      /* enable UART0 clock                */

	  /* Configure UART0 Pins (PA10 = TX, PA9 = RX). */
  PIOA->PIO_IDR        =  (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0);
	
	ul_sr = PIOA->PIO_ABCDSR[0];
	PIOA->PIO_ABCDSR[0] &= (~(PIO_PA9A_URXD0 | PIO_PA10A_UTXD0) & ul_sr);
	ul_sr = PIOA->PIO_ABCDSR[1];
	PIOA->PIO_ABCDSR[1] &= (~(PIO_PA9A_URXD0 | PIO_PA10A_UTXD0) & ul_sr);

  PIOA->PIO_PDR        =  (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0);
	PIOA->PIO_PUDR       =  (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0);
	
  /* Configure UART0 for 115200 baud. */
  UART0->UART_CR   = (UART_CR_RSTRX | UART_CR_RSTTX) |
                     (UART_CR_RXDIS | UART_CR_TXDIS);
	UART0->UART_BRGR = (SystemCoreClock / 115200) / 16;
  UART0->UART_MR   =  (0x4u <<  9);        /* (UART) No Parity                 */
  UART0->UART_CR   = UART_CR_RXEN | UART_CR_TXEN;
	
	PMC->PMC_WPMR = 0x504D4301;             /* Enable write protect             */
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
	while (!(UART0->UART_SR & UART_SR_TXRDY));
	UART0->UART_THR = c;
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
			LOS_EvbUartWriteByte(*str++);
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
    while((UART0->UART_SR & UART_SR_RXRDY) == 0);
    *c = UART0->UART_RHR;
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

#ifndef LOS_KERNEL_TEST_KEIL_SWSIMU
///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口USART */
		LOS_EvbUartWriteByte(ch);	
	
		return (ch);
}
#endif

