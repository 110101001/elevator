#include<unistd.h>
#include<pthread.h>
#include<time.h>

#include"elevator_ctrl_ui.h"
#include"ele.h"
#include"smemory.h"
#include"floor_ui.h"
#include"process.h"


void clicked_to(int floor){
    ele_task *temp;
    temp=malloc(sizeof(ele_task));
    for(int i=0;i<4;i++){
        shm_read(ele_task_addr+i,temp,sizeof(ele_task));
        if(temp->floor==-1){
            temp->floor=floor;
            temp->time=time(0);
            shm_write(ele_task_addr+i,temp,sizeof(ele_task));
        }
    }

};
    

void ele_print()
{
    state out;
    while(1){
        P(time_to_display);
        shm_read(shmaddr,(byte*)&out,sizeof(state));
        if(out.dir==DOWN)
        {
            gtk_arrow_set(GTK_ARROW(ele_dir),GTK_ARROW_DOWN,GTK_SHADOW_ETCHED_IN);
        }

        else
        {
            gtk_arrow_set(GTK_ARROW(ele_dir),GTK_ARROW_UP,GTK_SHADOW_ETCHED_IN);
        }
        char ch_out[10];
        sprintf(ch_out,"%.0fF",out.floor);
        gtk_label_set_text(GTK_LABEL(now_floor),ch_out);
        gtk_widget_show(ele_dir);
        gtk_widget_show(now_floor);
        usleep(100000);
    }
}

void create_ele_ui()
{

    gtk_init(&argc,&argv);
    ele_builder=gtk_builder_new();
    gtk_builder_add_from_file(ele_builder,"in_lift.glade",NULL);
    ele_window=GTK_WIDGET(gtk_builder_get_object(ele_builder,"window"));
    to_1=GTK_WIDGET(gtk_builder_get_object(ele_builder,"to_1"));
    to_2=GTK_WIDGET(gtk_builder_get_object(ele_builder,"to_2"));
    to_3=GTK_WIDGET(gtk_builder_get_object(ele_builder,"to_3"));   
    now_floor=GTK_WIDGET(gtk_builder_get_object(ele_builder,"now_floor"));
    ele_dir=GTK_WIDGET(gtk_builder_get_object(ele_builder,"dir"));
    open_door=GTK_WIDGET(gtk_builder_get_object(ele_builder,"open"));
    close_door=GTK_WIDGET(gtk_builder_get_object(ele_builder,"close"));
    plan=GTK_WIDGET(gtk_builder_get_object(ele_builder,"plan"));
    gtk_builder_connect_signals (ele_builder, NULL);
    gtk_window_set_title(GTK_WINDOW(ele_window), "ELEVATOR");
    g_signal_connect(GTK_BUTTON(to_1), "clicked", G_CALLBACK(clicked_to), 1);
    gtk_widget_show_all(ele_window);
    pthread_t tid;
    pthread_create(&tid,NULL,ele_print,NULL);
    gtk_main();
 }


void set_ele_state(){
    state input;
    shm_read(shmaddr,(byte*)&input,sizeof(state));
    input.floor=input.floor+1;
    if(input.dir==DOWN)
    {
        input.dir=UP;
        gtk_arrow_set(GTK_ARROW(ele_dir),GTK_ARROW_DOWN,GTK_SHADOW_ETCHED_IN);
    }

    else
    {
        input.dir=DOWN;
        gtk_arrow_set(GTK_ARROW(ele_dir),GTK_ARROW_UP,GTK_SHADOW_ETCHED_IN);
    }
    shm_write(shmaddr,(byte*)&input,sizeof(state));
    char out[10];
    sprintf(out,"%f",input.floor);
    gtk_label_set_text(GTK_LABEL(now_floor),out);
    gtk_widget_show(now_floor);
}


