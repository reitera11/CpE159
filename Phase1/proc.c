// proc.c, 159
// all user processes are coded here
// processes do not R/W kernel data or code, must use syscalls
// OS bootstrap and The Kernel for OS phase 1
//
// Team Name: Alex (Members: Alex Reiter)

#include "include.h"
#include "data.h"
#include "proc.h"

void InitProc(void) {
   int i;
  // unsigned short *p;

  // p->0xb8000; // upper-left corner of display

   while(1) {
      cons_printf("."); //show the dot
      for (i = 0; i < LOOP / 2; i++){//wait for half of LOOP: loop on asm("inb $0x80");
		  asm("inb $0x80");
	  }

      cons_clear(); //erase above writing
      for (i = 0; i < LOOP / 2; i++){//wait for half of LOOP: loop on asm("inb $0x80");
		  asm("inb $0x80");
	  }
   }
}

void UserProc(void) {
   int i;
   //unsigned short *p;

   while(1) {
	  int a, b;
	  a = cur_pid / 10;
	  b = cur_pid % 10;
     // p->(0xb8000 + cur_pid);
      cons_printf("%i", a); //show 1st digit of its PID
     // p->p + 1;
      cons_printf("%i", b); //show 2nd digit of its PID
      for (i = 0; i < LOOP / 2; i++){//wait for half of LOOP: loop on asm("inb $0x80");
		  asm("inb $0x80");
      }
      cons_clear();
      for (i = 0; i < LOOP / 2; i++){//wait for half of LOOP: loop on asm("inb $0x80");
		  asm("inb $0x80");
   }
  }
}
