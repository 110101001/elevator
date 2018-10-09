#include<unistd.h>

#include"pipe.h"
#include"ctrler.h"
#include"process.h"



int create_process(){
    int flag;
    if(flag=create_floor_process(FLOOR1)==-1) return -1;
    if(flag=create_floor_process(FLOOR2)==-1) return -1;
    if(flag=create_floor_process(FLOOR3)==-1) return -1;
    if(flag=create_electl_process()==-1) return -1;
    return 0;
}

int create_electl_process(){
    int flag;
    if(flag=fork()==0){
        electl_main_loop();
    }
    else if(flag==-1) 
        return -1;
    else
        return 0;
}

int create_floor_process(int floor){
    int flag;
    if(flag=fork()==0){
        floor_main_loop(floor);
    }
    else if(flag==-1) 
        return -1;
    else
        return 0;
}
