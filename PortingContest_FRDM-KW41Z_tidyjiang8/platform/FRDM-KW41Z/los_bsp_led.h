#ifndef _LOS_BSP_LED_H
#define _LOS_BSP_LED_H

#define LED3_B0 		0  // PORTB0
#define LED_RED_C1 		1  // PORTC1
#define LED_GREEN_A19 	19 // PORTA19
#define LED_BLUE_A18 	18 // PORTA18
#define LED_4

#define LED_ON	(1)
#define LED_OFF	(0)
#define LOS_LED1	(0)
#define LOS_LED2	(1)
#define LOS_LED3	(2)
#define LOS_LED4	(3)
#define LOS_LEDX	(4)


void LOS_EvbLedInit(void);
void LOS_EvbLedControl(int index, int cmd);
#endif
