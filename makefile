CFLAGS=`pkg-config --cflags --libs gtk+-3.0  gthread-2.0`   -g    -export-dynamic -pthread
OBJ=elevator
SRC=ele.h ele.c main.c process.c process.h floor_ui.c floor_ui.h schedule.c smemory.h smemory.c elevator_ctrl_ui.h elevator_ctrl_ui.c
all:
	    gcc   -o   $(OBJ)    $(SRC)    $(CFLAGS)
clean:
	    rm -f          $(OBJ)

