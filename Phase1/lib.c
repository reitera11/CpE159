// lib.c, 159
// OS bootstrap and The Kernel for OS phase 1
//
// Team Name: Alex (Members: Alex Reiter)

#include "include.h"
#include "types.h"
#include "data.h"

// clear DRAM data block, zero-fill it
void Bzero(char *p, int bytes) {
   while(bytes--) *p++ = 0;
}

int QisEmpty(q_t *p) { // return 1 if empty, else 0
   return (p->count == 0);
}

int QisFull(q_t *p) { // return 1 if full, else 0
   return (p->count == PROC_MAX);
}

// dequeue, 1st integer in queue
// if queue empty, return -1
int DeQ(q_t *p) { // return -1 if q[] is empty
   int i, data = 0;

   if(QisEmpty(p)) {
      return -1;
   }

   data = p->q[0];
   p->bytes--;
   
   for(i = 0; i < Q_SIZE-1; i++){
	p->q[i] = p->q[i+1];
   }
   return data;
}

// if not full, enqueue integer to tail slot in queue
void EnQ(int to_add, q_t *p) {
   if(QisFull(p)) {
      cons_printf("Kernel panic: queue is full, cannot EnQ!\n");
      breakpoint();
   }

   p->q[p->bytes] = to_add;
   p->bytes++;
}

