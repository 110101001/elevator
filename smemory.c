#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<errno.h>
#include"ele.h"
#include"smemory.h"
/*
   shm_write(地址（基址变量名叫shmaddr），数据指针，数据长度)；
   shm_read(地址（基址变量名叫shmaddr），数据指针，数据长度)；
   */
int shmid=0;
int semid=0;
byte *shmaddr;
state *stateaddr;
ele_task *ele_task_addr;
floor_task *floor_task_addr;

extern int errno;

void P(int semid){
    struct sembuf Sembuf={0,-1,0};
    semop(semid,&Sembuf, 1);
}

void V(int semid){
    struct sembuf Sembuf={0,1,0};
    semop(semid,&Sembuf, 1);
}

void shm_init(){
    key_t key=ftok(".",0x100);
    shmid=shmget(key,SHMSIZE,IPC_CREAT|0666);
    if(shmid<0)
    {
        printf("shm init erro\n");
        return;
    }
    shmaddr=shmat(shmid,NULL,0);

    stateaddr=(state *)shmaddr;
    ele_task_addr=(ele_task *)(shmaddr+sizeof(state));
    floor_task_addr=(floor_task *)(ele_task_addr+4*sizeof(ele_task));
    for(int i=0;i<3;i++)
        (ele_task_addr+i)->floor=-1;

    for(int i=0;i<4;i++)
        (floor_task_addr+i)->floor=-1;

    //printf("%s\n",strerror(errno));
    semid=semget(key,1,IPC_CREAT|0644);
    time_to_display=semget((key_t)"1234",6,0666|IPC_CREAT);
    semctl(semid,0,SETVAL,1);
    semctl(time_to_display,0,SETVAL,1);
    return;
}

void shm_write(byte *addr,byte *data,int len){
    P(semid);
    memcpy(addr,data,len);
    V(semid);
}

void shm_read(byte *addr,byte *data,int len){
    P(semid);
    memcpy(data,addr,len);
    V(semid);
}

void shm_test(){
    byte buf[10];
    for(int i=0;i<20;i++){
        for(int j=0;j<10;j++) buf[j]=i+j;
        shm_write(shmaddr+20*i,buf,10);
    }
    for(int i=0;i<20;i++){
        shm_read(shmaddr+20*i,buf,10);
        for(int j=0;j<10;j++){
            if(!buf[j]==i+j) {
                printf("Shm error!\n");
                exit(0);
            }
        }
    }
}
