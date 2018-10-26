#include"ele.h"
#include"smemory.h"
#include<stdlib.h>

int schedule(){
    time_t min=-1;
    int floor=-1;
    {
        floor_task *temp;
        temp=malloc(sizeof(floor_task));
        shm_read(floor_task_addr,temp,sizeof(floor_task));
        temp->time=-1;
        for(int i=0;i<4;i++){
            shm_read(floor_task_addr+i,temp,sizeof(floor_task));
            if(temp->floor!=-1){
                if(temp->time<min||min==-1){
                    min=temp->time;
                    floor=temp->floor;
                    break;
                }   
            }
        }
    }
    {
        ele_task *temp;
        temp=malloc(sizeof(ele_task));
        temp->time=-1;
        for(int i=0;i<3;i++){
            shm_read(ele_task_addr+i,temp,sizeof(ele_task));
            if(temp->floor!=-1){
                if(temp->time<min||min==-1){
                    min=temp->time;
                    floor=temp->floor;
                    break;
                }   
            }
        }
    }
    return floor;
}
