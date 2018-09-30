// types.h, 159
// OS bootstrap and The Kernel for OS phase 1
//
// Team Name: Alex (Members: Alex Reiter)

#ifndef __TYPES__
#define __TYPES__

#include "constants.h"

typedef void (*func_p_t)(void); // void-return function pointer type

typedef enum {AVAIL, READY, RUN} state_t;

typedef struct {
   unsigned int reg[8];
   unsigned int eip;
   unsigned int cs;
   unsigned int efl;
} TF_t;

typedef struct {
   state_t state;                       // read in 1.html
   int cpu_time;
   int cpu_life;
   TF_t *TF_p;
   } pcb_t;                     

typedef struct {             // generic queue type
  int q[Q_SIZE];                      // for a circular queue
  int bytes;
  int count;
} q_t;

#endif
