#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include "testandset.h"


void init(str_lock *my_struct_lock){
    my_struct_lock = malloc(sizeof(str_lock));
    my_struct_lock->lock=0;
}

void lock(str_lock *my_struct_lock){
    int *target= &(my_struct_lock->lock);
    __asm__ ( "enter:"
              "movl $1, %%eax;"
              "xchgl %%eax, %0;"
              "testl %%eax, %%eax;"   //set ZF to 1 if eax == 0
              "jnz enter;"           //saute si eax n'est pas 0  
              :"=m"(*target) /* related to %0*/
              :
              :"eax");         
}
     
     
void unlock(str_lock *my_struct_lock){          
    int *target= &(my_struct_lock->lock);
    __asm__ ( "movl $0, %%eax;"
              "xchgl %%eax, %0;"
              :"=m"(*target) /* related to %0*/
              :
              :"%eax"); 
}