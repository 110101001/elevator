#include<unistd.h>
#include<stdio.h>
#include"smemory.h"
#include"ele.h"
#include"ctrler.h"


int target_floor=0;
int position=0;
DOOR door=CLOSE;
DIR dir=STOP;
int stage=0;

int schedule(){
    if(stage==0) return FLOOR2;
    if(stage==1) return FLOOR1;
    if(stage==2) return FLOOR3;
    if(stage==3) return FLOOR2;
    if(stage==4) exit(0);
}

void ele_arrive(){
    stage+=1;
}

void ele_state_update(){
    state stat;
    stat.floor=(position*1.0)/(TICK_PER_FLOOR*1.0);
    stat.dir=dir;
    stat.door=door;
    
    shm_write(stateaddr,(byte *)&stat ,sizeof(state));
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
    }
    //
}