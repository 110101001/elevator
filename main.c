#include<stdio.h>
#include<unistd.h>

#include"pipe.h"
#include"ctrler.h"

int main(){

    pipe_init();

    create_process();
}