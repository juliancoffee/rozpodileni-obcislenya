#pragma once
#include "data.h"

void update_info(GtkWidget *text_view, struct computation_context_t *ctx);
void show_error(GtkWidget *error_view, char *error_msg);
