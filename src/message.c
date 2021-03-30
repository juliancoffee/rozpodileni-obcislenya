#include "globals.h"

extern struct GlobalData global_data;

char *info_text(void) {
  char *msg_buf = calloc(1000, sizeof(char));
  snprintf(msg_buf, 1000,
           "Is synced: %s\n"
           "Number of threads: %zu\n"
           "%zu*%zu pixels image",
           global_data.is_sync ? "true" : "false", global_data.num_threads,
           global_data.pixels, global_data.pixels);
  return msg_buf;
}
