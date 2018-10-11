#include<stdio.h>
#include<unistd.h>

#include"smemory.h"
#include"ctrler.h"
#include"process.h"

int main(){
    shm_init();
    
    create_process();

    ele_main_loop();
}