#pragma once
#include "globals.h"

void draw_button_cb(struct binded_widget_t *bind);
void compute_button_cb(struct computation_context_t *ctx);
void sync_button_cb(struct binded_widget_t *bind);
void async_button_cb(struct binded_widget_t *bind);
