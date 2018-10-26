#ifndef ElE_H_
#define ElE_H_
#include<sys/types.h>

#define ABS(x) ((x)>0?(x):-(x))
#define VEL 10
#define TICK_PER_FLOOR 100

#define FLOOR1 0
#define FLOOR2 1
#define FLOOR3 2
#define ELE 3

typedef enum{STOP,UP,DOWN} DIR;
typedef enum{OPEN,CLOSE} DOOR;

typedef struct state{
    float floor;
    DIR dir;
    DOOR door;
}state;

typedef struct floor_task{
    int floor;//呼叫电梯的楼层
    DIR dir;//呼叫者要去的方向
    time_t time;
}floor_task;

typedef struct ele_task{
    int floor;//电梯要去的楼层
    time_t time;
}ele_task;
//floor取-1表示队列末尾
void ele_main_loop();

#endif
