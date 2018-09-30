// data.h, 159 test test
// kernel data are all declared in main.c during bootstrap
// kernel .c code reference them as 'extern'
// OS bootstrap and The Kernel for OS phase 1
//
// Team Name: Alex (Members: Alex Reiter)

#ifndef __DATA__
#define __DATA__

#include "types.h"             // defines q_t, pcb_t, PROC_MAX, STACK_SIZE

extern int cur_pid;            // PID of current selected running process
extern q_t ready_q, avail_q;                             // prototype the rest...
extern pcb_t pcb[PROC_MAX];
extern char proc_stack[PROC_MAX][STACK_SIZE];

#endif                         // endif of ifndef
