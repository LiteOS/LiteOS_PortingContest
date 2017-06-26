#ifndef _LOS_BSP_KEY_H
#define _LOS_BSP_KEY_H

#define BUTTON_PB0 (1 << 0)
#define BUTTON_PB1 (1 << 1)

#define LOS_KEY_PRESS BUTTON_PB0

#define USER_KEY 1

extern void LOS_EvbKeyInit(void);

unsigned int LOS_EvbGetKeyVal(int KeyNum);

#endif

