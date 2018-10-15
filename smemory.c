#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<errno.h>
#include"smemory.h"
/*
shm_write(地址（基址变量名叫shmaddr），数据指针，数据长度)；
shm_read(地址（基址变量名叫shmaddr），数据指针，数据长度)；
*/
int shmid=0;
int semid=0;
byte *shmaddr;

extern int errno;

static void P(int semid){
    struct Sembuf sembuf={0,-1,0};
    semop(semid,sembuf, 1);
}

static void V(int semid){
    struct Sembuf sembuf={0,1,0};
    semop(semid,sembuf, 1);
}

void shm_init(){
    key_t key=ftok(".",0x100);
    shmid=shmget(key,SHMSIZE,IPC_CREAT|0666);
    shmaddr=shmat(shmid,NULL,0);
    //printf("%s\n",strerror(errno));
    semid=semget(key,1,IPC_CREAT|0644);
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