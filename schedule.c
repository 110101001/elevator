#include"ele.h"
#include"smemory.h"
#include<stdlib.h>

int* schedule(){


    printf("enter schedule\n");
    {
        floor_task *temp;
        temp=malloc(sizeof(floor_task));
        shm_read(floor_task_addr,temp,sizeof(floor_task));
        temp->time=-1;
        for(int i=0;i<4;i++){
            shm_read(floor_task_addr+i,temp,sizeof(floor_task));
            if(temp->floor==-1)
                break;
            if(search_queue(temp->floor))
            {
                continue;
            }
            else 
            {
                forced_insert_queue(temp->floor);
            }
            printf("ahgjkk %d\n",temp->floor);


        }
        temp->floor=-1;
        for(int i=0;i<4;i++)
            shm_write(floor_task_addr+i,temp,sizeof(floor_task));
    


    }
    {
        ele_task *temp;
        temp=malloc(sizeof(ele_task));
        temp->time=-1;
        for(int i=0;i<3;i++){
            shm_read(ele_task_addr+i,temp,sizeof(ele_task));
            if(temp->floor==-1){
                break;
            }
            printf("temp->floor%d\n",temp->floor);
            insert_queue(temp->floor);




        }

        temp->floor=-1;
        for(int i=0;i<4;i++)
        shm_write(ele_task_addr+i,temp,sizeof(ele_task));

    }
    return queue;
}
