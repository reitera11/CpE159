// main.c, 159
// OS bootstrap and The Kernel for OS phase 1
//
// Team Name: Alex (Members: Alex Reiter)

#include "include.h"  // given SPEDE stuff
#include "types.h"    // kernle data types
#include "lib.h"      // small handly functions
#include "proc.h"     // all user process code here
#include "isr.h"      // kernel ISR code
#include "entry.h"    // entries to kernel (TimerEntry, etc.)

// kernel data are all here:
int cur_pid;                        // current running PID; if -1, none selected
q_t ready_q, avail_q;               // avail PID and those created/ready to run
pcb_t pcb[PROC_MAX];                // Process Control Blocks
char stack[PROC_MAX][STACK_SIZE];   // process runtime stacks

void InitKernel(void) {             // init and set up kernel!
   int i;
   struct i386_gate *IVT_p;         // IVT's DRAM location

   IVT_p = get_idt_base();          // get IVT location
   fill_gate(IVT_p, (int)Loader,get_cs(), ACC_INTR_GATE, 0);                  // fill out IVT for timer
   outportb(PIC_MASK, MASK);                   // mask out PIC for timer

   Bzero((char *)&ready_q, sizeof(q_t));                      // clear 2 queues
   Bzero((char *)&avail_q, sizeof(q_t));
   for(i=1; i < PROC_MAX; i++){             // add all avail PID's to the queue
		pcb[i].state = AVAIL;
		EnQ(i, &avail_q);
   }
   cur_pid = -1;
}

void Scheduler(void) {             // choose a cur_pid to run
   if(cur_pid > 0) return; // a user PID is already picked

   if(ready_q.bytes == 0 && cur_pid == 0) return; // InitProc OK

   if(ready_q.bytes == 0 && cur_pid == -1) {
      cons_printf("Kernel panic: no process to run!\n");
      breakpoint();                                  // to GDB we go
   }

   if(cur_pid != -1) {
      cur_pid = DeQ(&ready_q); // suspend cur_pid
      pcb[cur_pid].state = RUN;
   }
   cur_pid = DeQ(&ready_q); // pick a user proc

   pcb[cur_pid].cpu_time = 0;                          // reset process time
   pcb[cur_pid].state = RUN;                          // change its state
}

int main(void) {                       // OS bootstraps
   InitKernel();

   InitProc();            // create InitProc
   Scheduler(); //to set cur_pid to the 1st PID;
   Loader(pcb[cur_pid].TF_p);         // load proc to run

   return 0; // statement never reached, compiler needs it for syntax
}

void TheKernel(TF_t *TF_p) {           // kernel runs
   char ch;

   pcb[cur_pid].TF_p = TF_p; // save TF addr

   TimerISR();                     // handle tiemr event

   if(cons_kbhit()){                  // if keyboard pressed
      ch = cons_getchar();
      if(ch == 'b'){                     // 'b' for breakpoint
		     breakpoint();                        // go into GDB
         }
      if(ch == 'n'){                     // 'n' for new process
		NewProcISR(UserProc);} // create a UserProc
   }
   Scheduler(); // which may pick another proc
   Loader(pcb[cur_pid].TF_p); // load proc to run!
}

