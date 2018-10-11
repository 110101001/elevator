#ifndef PIPE_H_
#define PIPE_H_

 
typedef unsigned char byte;

int pipe_init();
void pipe_send(int sender,byte *data,int len);
int pipe_recv(int sender,byte *data,int len);

#endif
