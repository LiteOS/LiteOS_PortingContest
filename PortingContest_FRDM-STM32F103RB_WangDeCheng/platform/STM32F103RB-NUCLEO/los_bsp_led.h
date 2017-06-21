#ifndef _LOS_BSP_LED_H
#define _LOS_BSP_LED_H

#define LED_ON      (1)
#define LED_OFF     (0)
#define LOS_LED1    (0)
#define LOS_LED2    (1)
#define LOS_LED3    (2)
#define LOS_LED4    (3)
#define LOS_LEDX    (4)

/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
// R-红色
#define LED1_GPIO_PORT    	GPIOA			            /* GPIO端口 */
#define LED1_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED1_GPIO_PIN		GPIO_Pin_5			        /* 连接到SCL时钟线的GPIO */

// G-绿色
#define LED2_GPIO_PORT    	GPIOA			            /* GPIO端口 */
#define LED2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED2_GPIO_PIN		GPIO_Pin_5			        /* 连接到SCL时钟线的GPIO */

// B-蓝色
#define LED3_GPIO_PORT    	GPIOA		            /* GPIO端口 */
#define LED3_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED3_GPIO_PIN		GPIO_Pin_1			        /* 连接到SCL时钟线的GPIO */


void LOS_EvbLedInit(void);
void LOS_EvbLedControl(int index, int cmd);
#endif
