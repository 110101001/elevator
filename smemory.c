#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include"smemory.h"

int shmid=0;
int semid=0;
byte *shmaddr;

static void P(int semid){
    struct Sembuf sembuf={0,-1,0};
    semop(semid,sembuf, 1);
}

static void V(int semid){
    struct Sembuf sembuf={0,1,0};
    semop(semid,sembuf, 1);
}

void shm_init(){
    key_t key=ftok(".",0x6666);
    shmid=shmget(key,SHMSIZE,IPC_CREAT|IPC_EXCL|0666);
    shmaddr=shmat(shmid,NULL,0);
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