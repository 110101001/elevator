#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#include"smemory.h"
#include"ele.h"
#include"schedule.h"


#define close 0
#define open 1

DOOR door=CLOSE;
DIR_ dir=STOP;
int stage=0;

void forced_insert_queue(int value){
    queue[sub]=value;
    sub++;

}

void insert_queue(int value){
    if(value>position)
    {
        for(int i=0;i<10;i++)
        {
            if(queue[i]==-1&&i!=0)
                break;
            if(value>queue[i]||queue[0]==-1)
            {
                queue[sub]=value;
                sub++;
                break;
            }
        }
    }
    else if(value<position)
    {
        for(int i=0;i<10;i++)
        {
            if(queue[i]==-1&&i!=0)
                break;
            if(value<queue[i]||queue[0]==-1)
            {
                queue[sub]=value;
                sub++;
                break;
            }
        }
    }

}

int pop_queue(){
    int ret=queue[0];
    for(int i=0;i<9;i++)
        queue[i]=queue[i+1];
    sub--;
    return ret;
}

bool search_queue(int value){
    for(int i=0;i<10;i++)
        if(queue[i]==value)
            return true;
    return false;
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
    Del_task();
    dir=STOP;
}

void ele_state_update(int pos,DIR_ dir1,DOOR dor){
    state stat;
    stat.floor=pos;
    stat.dir=dir1;
    stat.door=dor;
    shm_write(stateaddr,(byte *)&stat ,sizeof(state));
    for(int i=0;i<6;i++){
        V(time_to_display);
    }
}

void ele_move(){
    while(1){

        if(queue[0]==-1)
            break;
        while(1){
        if(queue[0]<position)
            ele_state_update(position,DOWN,CLOSE);
        else
            ele_state_update(position,UP,CLOSE);
        if(queue[0]==position)
            break;
        if(queue[0]-position>0)
            position++;
        else 
            position--;
        sleep(2);
    }
    position=queue[0];
    pop_queue();
    }
    
}

void ele_main_loop(){
    ele_state_update(1,UP,CLOSE);
    for(int i=0;i<10;i++)
        queue[i]=-1;
    position=1;
    sub=0;
    state stat;
    shm_read(stateaddr,(byte *)&stat,sizeof(state));
    while(1){
        while(stat.door==OPEN)
        {
            usleep(100000);
            shm_read(stateaddr,(byte *)&stat,sizeof(state));
        }
        schedule();
        ele_move();
        usleep(1000000);
    }
    //
}
