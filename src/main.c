#include "globals.h"
#include "gui.h"

struct GlobalData global_data = {
    .comp_ctx = NULL,
    .palette = {.data = NULL, .len = 0},
    .surface = NULL,
};

// TODO: increase and decrease number of threads
// TODO: implement pausing
// TODO: implement clearing of image
int main(int argc, char **argv) {
  global_data.comp_ctx = malloc(sizeof(struct computation_context_t));
  global_data.comp_ctx->is_sync = true;
  global_data.comp_ctx->num_threads = 4;
  global_data.comp_ctx->set = NULL;

  char *img_size_request = getenv("IMG_SIZE");

  if (img_size_request != NULL) {
    global_data.comp_ctx->pixels = atoi(img_size_request);
  } else {
    global_data.comp_ctx->pixels = 500;
  }
  int status = start_app(argc, argv);
  return status;
}
