#pragma once
#include <gtk/gtk.h>

void draw_button_cb(GtkWidget *drawing_area);
void calculate_button_cb(gpointer _data);
void sync_button_cb(GtkWidget *text_view);
void async_button_cb(GtkWidget *text_view);
