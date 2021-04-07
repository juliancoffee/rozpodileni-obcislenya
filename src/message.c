#include "message.h"
#include "data.h"

static char *current_time(void) {
  time_t raw;
  time(&raw);
  return ctime(&raw);
}

static char *info_text(struct computation_context_t *ctx) {
  bool is_sync = ctx->is_sync;
  uint16_t num_threads = ctx->num_threads;
  size_t pixels = ctx->pixels;
  atomic_bool is_paused = *ctx->is_paused;

  size_t buflen = 1000;
  char *msg_buf =
      calloc_or_die(buflen, sizeof(char), "allocating buffer for message");

  snprintf(
      msg_buf,
      buflen - 1, /* one byte for '\0'*/
      " Is synced: %s\n"
      " Is paused: %s\n"
      " Number of threads: %hd\n"
      " Image size: %zu*%zu pixels",
      is_sync ? "true" : "false",
      is_paused ? "true" : "false",
      num_threads,
      pixels,
      pixels);
  return msg_buf;
}

void update_info(GtkWidget *text_view, struct computation_context_t *ctx) {
  GtkTextBuffer *buf = gtk_text_view_get_buffer((GtkTextView *) text_view);
  char *msg = info_text(ctx);
  gtk_text_buffer_set_text(buf, msg, -1);
  free(msg);
}

void show_error(GtkWidget *error_view, char *error_msg) {
  GtkTextBuffer *buf = gtk_text_view_get_buffer((GtkTextView *) error_view);
  size_t buflen = 1000;
  char *msg_buf =
      calloc_or_die(buflen, sizeof(char), "allocating buffer for message");
  char *time = current_time();
  snprintf(
      msg_buf,
      buflen - 1, /* one byte for '\0'*/
      "%s: %s\n",
      time,
      error_msg);
  gtk_text_buffer_set_text(buf, msg_buf, -1);
}
