/**
 * Author: Mark Gottscho
 * Email: mgottscho@ucla.edu
 * 
 * Hello World example for RISC-V. This is a playground for implementing application-defined memory DUE handlers.
 */ 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <memory_due.h> 
#include "hello.h"
#include "sdecc_handlers.h"

float x[ARRAY_SIZE];
float y[ARRAY_SIZE];

int main(int argc, char** argv) {
    unsigned long i;
    int injected_init, injected_compute = 0;

    EN_RECOVERY(main,i,sizeof(unsigned long))
    EN_RECOVERY_PTR(main,x,ARRAY_SIZE*sizeof(float))
    EN_RECOVERY_PTR(main,y,ARRAY_SIZE*sizeof(float))

    BEGIN_DUE_RECOVERY(main, overall, STRICTNESS_STRICT) 
    BEGIN_DUE_RECOVERY(main, init, STRICTNESS_STRICT)
    //Initialization
    i = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
        //Semi-controlled data injection
        /*if (!injected_init && i == ARRAY_SIZE-10) {
            injected_init = 1;
            INJECT_DUE_DATA(0,0)
        }*/
        x[i] = (float)(i)/10;
    }
    END_DUE_RECOVERY(main, init)
   
    BEGIN_DUE_RECOVERY(main, compute, STRICTNESS_DEFAULT)
    //Computation
    for (i = 0; i < ARRAY_SIZE; i++) {
        //Semi-controlled data injection
        if (!injected_compute && i % 10 == 0) {
            injected_compute = 1;
            INJECT_DUE_INSTRUCTION(1,10)
        }
        y[i] = sin(x[i]);
    }
    END_DUE_RECOVERY(main, compute)
   
    //Sine printout viz
    long spot = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
       spot = (long)(y[i]*60)+60; 
       for (long j = 0; j < spot; j++)
           printf(" ");
       printf("*");
       for (long j = spot; j < 120; j++)
           printf(" ");
       printf("\n");
    }
    for (i = 0; i < ARRAY_SIZE; i++)
        printf("x[%d]: %.8f    y[%d]: %.8f\n", i, x[i], i, y[i]);
    printf("Hello World!\n");
    
    //Report DUE information from each region
    dump_dueinfo(&DUE_INFO(main, overall));
    dump_dueinfo(&DUE_INFO(main, init));
    dump_dueinfo(&DUE_INFO(main, compute));
    
    END_DUE_RECOVERY(main, overall)

    return 0;
}
