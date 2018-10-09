#include<unistd.h>
#include<stdio.h>
#include"pipe.h"
#include"ctrler.h"

int floor_main_loop(int floor){
    printf("floormainloop %d \n",floor);
    return 0;
}

int electl_main_loop(){
    printf("electrlmainloop\n");
    return 0;
}

int floor_op_loop(){

}

int floor_display_loop(){

}

int electl_op_loop(){

}

int electl_display_loop(){
    
}