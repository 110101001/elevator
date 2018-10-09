#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#include"pipe.h"
#include"ctrler.h"
#include"display.h"

int self; 

void floor_op_loop(){
    printf("Floor %d op init at pid:%d\n",self,getpid());
    sleep(1);
    exit(0);
}


void electl_op_loop(){
    printf("Ele op init at pid:%d\n",getpid());
    sleep(1);
    exit(0);
}

int floor_main_loop(int floor){
    pthread_t tid;
    self=floor;
    pthread_create(&tid,NULL,floor_display_loop,NULL);
    floor_op_loop();
    return 0;
}

int electl_main_loop(){
    pthread_t tid;
    self=ELE;
    pthread_create(&tid,NULL,electl_display_loop,NULL);
    electl_op_loop();
    return 0;
}