#ifndef PIPE_H_
#define PIPE_H_

#define FLOOR1 0
#define FLOOR2 1
#define FLOOR3 2
#define ELE 3
 
typedef unsigned char byte;

int pipe_init();
void pipe_send(int sender,byte *data,int len);
int pipe_recv(int sender,byte *data,int len);

#endif
