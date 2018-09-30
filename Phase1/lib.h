// lib.h, 159
// OS bootstrap and The Kernel for OS phase 1
//
// Team Name: Alex (Members: Alex Reiter)

#ifndef _LIB_
#define _LIB_

#include "types.h"

int Bzero(char *, int);
int QisEmpty(q_t *);
int QisFull(q_t *);
int DeQ(q_t *);
void EnQ(int, q_t *);

#endif