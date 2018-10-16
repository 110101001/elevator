#ifndef SMEMORY_H_
#define SMEMORY_H_

#define SHMSIZE 4*1024
/*
struct Sembuf{
    unsigned short num;
    short sem_op;
    short sem_flg;
};
*/
typedef unsigned char byte;

void shm_init();

void shm_write();

void shm_read();

void shm_test();

#endif