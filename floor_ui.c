#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


#include"floor_ui.h"
#include"smemory.h"
#include"ele.h"


void floor_display_loop(int floor)
{
    printf("enter onece more\n");
    state ele_state;
    while(1)
    {
        print_P(time_to_display);
        shm_read(shmaddr,(byte*)&ele_state,sizeof(state));
        if(ele_state.dir==DOWN)
        {
        //gdk_threads_enter();
            gtk_arrow_set(GTK_ARROW(floor1_dir),GTK_ARROW_DOWN,GTK_SHADOW_ETCHED_IN);
            gtk_widget_show(floor1_dir);
        // gdk_threads_enter();
        }
        else if(ele_state.dir==UP)
        {
            gtk_arrow_set(GTK_ARROW(floor1_dir),GTK_ARROW_UP,GTK_SHADOW_ETCHED_IN);
            gtk_widget_show(floor1_dir);
        }
        char out[10];
        sprintf(out,"%.1f",ele_state.floor);
        gtk_label_set_text(GTK_LABEL(nowfloor),out);
        gtk_widget_show(nowfloor);
        sprintf(out,"%.1f",old_floor);
        gtk_label_set_text(GTK_LABEL(floor1_rmntime),out);
        gtk_widget_show(floor1_rmntime);
        sleep(0.2);
    }
}





void ui_creat(int floor,int argc,int **argv)
{
    floor++;
    gtk_init(&argc,&argv);
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder,"floor.glade",NULL);
	floor1_window=GTK_WIDGET(gtk_builder_get_object(builder,"floor_1"));
	floor1_up=GTK_WIDGET(gtk_builder_get_object(builder,"up"));
	floor1_down=GTK_WIDGET(gtk_builder_get_object(builder,"down"));
	floor1_rmntime=GTK_WIDGET(gtk_builder_get_object(builder,"remntime"));	
	floor1_dir=GTK_WIDGET(gtk_builder_get_object(builder,"dir"));
 	nowfloor=GTK_WIDGET(gtk_builder_get_object(builder,"nowfloor"));
 	gtk_builder_connect_signals (builder, NULL);
    nowfloor=GTK_WIDGET(gtk_builder_get_object(builder,"nowfloor"));

    if(floor==1)
        gtk_window_set_title(GTK_WINDOW(floor1_window), "FLOOR  1");
    else if(floor==2)
        gtk_window_set_title(GTK_WINDOW(floor1_window), "FLOOR  2");
    else if(floor==3)
        gtk_window_set_title(GTK_WINDOW(floor1_window), "FLOOR  3");
    
    gtk_widget_show_all(floor1_window);
    pthread_t tid;
    pthread_create(&tid,NULL,floor_display_loop,floor);
    gtk_main();
}
	
