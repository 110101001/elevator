#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"pipe.h"

extern int self;

void floor_display_loop(){
    printf("Floor %d display init at pid:%d\n",self,getpid());
    exit(0);
}

void electl_display_loop(){
    printf("Ele display init at pid:%d\n",getpid());
    exit(0);
}