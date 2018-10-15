#include<stdio.h>
#include<unistd.h>

#include"smemory.h"
#include"ctrler.h"
#include"process.h"

extern byte *shmaddr;

int main(){
    shm_init();
    
    create_process();

    ele_main_loop();

}