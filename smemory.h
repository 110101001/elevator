#ifndef SMEMORY_H_
#define SMEMORY_H_
#include"ele.h"

#define SHMSIZE 4*1024

/*
struct Sembuf{
    unsigned short num;
    short sem_op;
    short sem_flg;
};
*/
typedef unsigned char byte;


extern state *stateaddr;
extern ele_task *ele_task_addr;
extern floor_task *floor_task_addr;

void shm_init();

void shm_write(byte *addr,byte *data,int len);

void shm_read(byte *addr,byte *data,int len);

void shm_test();

#endif
