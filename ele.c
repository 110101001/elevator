#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"smemory.h"
#include"ele.h"


int target_floor=0;
int position=0;
DOOR door=CLOSE;
DIR_ dir=STOP;
int stage=0;

int schedule(){
    return FLOOR2;
}

void Del_task(){
    if(position%TICK_PER_FLOOR==0){
        int floor=position/TICK_PER_FLOOR;
        {
            floor_task* temp;
            temp=malloc(sizeof(floor_task));
            for(int i=0;i<4;i++){
                shm_read(floor_task_addr+i,temp,sizeof(floor_task));
                if(temp->floor==floor){
                    temp->floor=-1;
                    shm_write(floor_task_addr+i,temp,sizeof(floor_task));
                }
            }
        }
        {
            ele_task *temp;
            temp=malloc(sizeof(ele_task));
            for(int i=0;i<3;i++){
                shm_read(ele_task_addr+i,temp,sizeof(ele_task));
                if(temp->floor==floor){
                    temp->floor=-1;
                    shm_write(ele_task_addr+i,temp,sizeof(ele_task));
                }
            }
        }
    }
}

void ele_arrive(){
    door=OPEN;
    exit(0);//做好了把这个删掉
}

void ele_state_update(){
    state stat;
    stat.floor=(position*1.0)/(TICK_PER_FLOOR*1.0);
    stat.dir=dir;
    stat.door=door;

    shm_write(stateaddr,(byte *)&stat ,sizeof(state));
    for(int i;i<6;i++){
        V(time_to_display);
    }
}

void ele_move(){
    int target_postion=target_floor*TICK_PER_FLOOR;
    if(target_postion!=position){
        if(target_postion>position){
            dir=UP;
        }
        else{
            dir=DOWN;
        }
        if(door==CLOSE){
            if(ABS(target_postion-position)<=VEL){
                position=target_postion;
                ele_arrive();
            }
            else{//ABS(target_postion-position)>100
                position+=(dir==UP)*VEL-(dir==DOWN)*VEL;
            }
        }
    }
}

void ele_main_loop(){
    printf("Ele init at pid:%d\n",getpid());
    ele_state_update();
    while(1){
        target_floor=schedule();
        ele_move();
        ele_state_update();
        usleep(10000);
    }
    //
}
