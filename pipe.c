#include<unistd.h>
#include<stdio.h>

#include"pipe.h"

int pipe_fd[4][2];

int pipe_init(){
    for(int i=0;i<4;i++)
        if(pipe(pipe_fd[i])) return -1;
    return 0;
}

void pipe_send(int *fd,byte *data,int len){
    close(fd[0]);
    write(fd[1],data,len);
}

int pipe_recv(int *fd,byte *data,int len){
    close(fd[1]);
    return read(fd[0],data,len);
}

