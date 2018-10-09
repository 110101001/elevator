#include<unistd.h>
#include<stdio.h>

#include"pipe.h"

int pipe_fd[4][2];
//init pipe, used in main
int pipe_init(){
    for(int i=0;i<4;i++)
        if(pipe(pipe_fd[i])) return -1;
    return 0;
}

//send msg 
void pipe_send(int sender,byte *data,int len){
    close(pipe_fd[sender][0]);
    write(pipe_fd[sender][1],data,len);
}
//recv msg
int pipe_recv(int sender,byte *data,int len){
    close(pipe_fd[sender][1]);
    return read(pipe_fd[sender][0],data,len);
}

