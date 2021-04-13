#pragma once
#include "data.h"

void draw_button_cb(struct binded_widget_pair_t *bind);
void compute_button_cb(struct computation_context_t *ctx);
void toggle_sync_button_cb(struct binded_widget_t *bind);
void toggle_pause_button_cb(struct binded_widget_t *bind);
void toggle_priority_button_cb(struct binded_widget_t *bind);
void increase_threads_cb(struct binded_widget_t *bind);
void decrease_threads_cb(struct binded_widget_t *bind);
