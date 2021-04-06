#include "message.h"
#include "data.h"

static char *info_text(struct computation_context_t *ctx) {
  bool is_sync = ctx->is_sync;
  size_t num_threads = ctx->num_threads;
  size_t pixels = ctx->pixels;

  size_t buflen = 1000;
  char *msg_buf = calloc(buflen, sizeof(char));

  snprintf(
      msg_buf,
      buflen,
      "Is synced: %s\n"
      "Number of threads: %zu\n"
      "%zu*%zu pixels image",
      is_sync ? "true" : "false",
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
