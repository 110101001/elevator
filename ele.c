#include<unistd.h>
#include<stdio.h>
#include"pipe.h"

void ele_main_loop(){
    printf("Ele init at pid:%d\n",getpid());
}