#include<stdio.h>
#include<unistd.h>

#include"smemory.h"
#include"ctrler.h"
#include"process.h"

extern byte *shmaddr;

int main(){
    shm_init();
    
    //create_process();

    //ele_main_loop();
    shm_write(shmaddr,"goodday!",9);
    byte buf[9];
    shm_read(shmaddr,buf,9);
    printf("%s\n",buf);

}