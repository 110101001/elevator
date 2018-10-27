#ifndef _ELEVATOR_CTRL_UI_H
#define _ELEVATOR_CTRL_UI_H
#endif


#include<gtk/gtk.h>


void create_ele_ui();

GtkBuilder* ele_builder;

GtkWidget* ele_window;
GtkWidget* to_1;
GtkWidget* to_2;
GtkWidget* to_3;
GtkWidget* ele_dir;
GtkWidget* now_floor;
GtkWidget* open_door;
GtkWidget* close_door;
GtkWidget* plan;
