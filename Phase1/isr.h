// isr.h, 159
// OS bootstrap and The Kernel for OS phase 1
//
// Team Name: Alex (Members: Alex Reiter)

#ifndef _ISR_  // prototype those in isr.c here
#define _ISR_

#include "types.h"

void NewProcISR(func_p_t);
void TimerISR(void);

#endif
