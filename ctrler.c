#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#include"smemory.h"
#include"ctrler.h"

int self; 

void floor_display_loop(){
    printf("Floor display %d init at pid:%d\n",self,getpid());
    pthread_exit(0);
}

void electl_display_loop(){
    printf("Ele display init at pid:%d\n",getpid());
    pthread_exit(0);
}

void floor_op_loop(){
    printf("Floor op %d init at pid:%d\n",self,getpid());
    pthread_exit(0);
}

void electl_op_loop(){
    printf("Ele op init at pid:%d\n",getpid());
    pthread_exit(0);
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