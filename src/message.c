#include "message.h"
#include "globals.h"

extern struct GlobalData global_data;

char *info_text(void) {
  struct computation_context_t *ctx = global_data.comp_ctx;
  bool is_sync = ctx->is_sync;
  size_t num_threads = ctx->num_threads;
  size_t pixels = ctx->pixels;

  size_t buflen = 1000;
  char *msg_buf = calloc(buflen, sizeof(char));

  snprintf(msg_buf,
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
