#include<unistd.h>
#include<pipe.h>

#include<ctrler.h>
#include<ele.h>



int create_process(){
    if(create_floor_process(FLOOR1)) return -1;
    if(create_floor_process(FLOOR2)) return -1;
    if(create_floor_process(FLOOR3)) return -1;
    if(create_electl_process()) return -1;
    return 0;
}

int create_electl_process(){
    int flag;
    if(flag=fork()==0){
        electrl_main_loop();
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
