#include<stdio.h>
#include<unistd.h>

#include"smemory.h"
#include"process.h"



int main(int argc_,char *argv_[]){
    argc=argc_;
    argv=argv_;
    shm_init();

    //shm_test();
    
    create_process();

    ele_main_loop();

}
