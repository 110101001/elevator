#include<unistd.h>

#include"ele.h"
#include"process.h"
#include"floor_ui.h"
#include"elevator_ctrl_ui.h"

int create_electl_process(){
    int flag;
    if(flag=fork()==0){
        //create_ele_ui();
        clicked_to(FLOOR2);
        sleep(1);
        clicked_to(FLOOR1);
        sleep(1);
        clicked_to(FLOOR3);
        exit(0);
    }
    else if(flag==-1) 
        return -1;
    else
        return 0;
}

int create_floor_process(int floor){
    int flag;
    if(flag=fork()==0){
        //ui_creat(floor);
        exit(0);
    }
    else if(flag==-1) 
        return -1;
    else
        return 0;
}

int create_process(){
    int flag;
    if(flag=create_floor_process(FLOOR1)==-1) return -1;
    if(flag=create_floor_process(FLOOR2)==-1) return -1;
    if(flag=create_floor_process(FLOOR3)==-1) return -1;
    if(flag=create_electl_process()==-1) return -1;
    return 0;
}
