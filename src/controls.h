#pragma once
#include "globals.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <gtk/gtk.h>

void draw_button_cb(GtkWidget *drawing_area);
void compute_button_cb(struct computation_context_t *ctx);
void sync_button_cb(GtkWidget *text_view);
void async_button_cb(GtkWidget *text_view);
