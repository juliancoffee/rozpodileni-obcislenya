#include "globals.h"
#include "gui.h"
#include "util.h"

// TODO: increase and decrease number of threads
// TODO: implement pausing
// TODO: implement clearing of image
int main(int argc, char **argv) {
  struct GlobalData global_data = {
      .comp_ctx = NULL,
      .draw_ctx = NULL,
  };

  struct computation_context_t *comp_ctx = NEW(struct computation_context_t);
  comp_ctx->is_sync = true;
  comp_ctx->num_threads = 4;
  comp_ctx->set = NULL;
  global_data.comp_ctx = comp_ctx;

  struct drawing_context_t *draw_ctx = NEW(struct drawing_context_t);
  struct palette_t palette = {.data = NULL, .len = 0};
  draw_ctx->palette = palette;
  draw_ctx->surface = NULL;
  global_data.draw_ctx = draw_ctx;

  char *img_size_request = getenv("IMG_SIZE");

  if (img_size_request != NULL) {
    global_data.comp_ctx->pixels = atoi(img_size_request);
  } else {
    global_data.comp_ctx->pixels = 500;
  }
  int status = start_app(argc, argv, &global_data);
  free(comp_ctx);
  free(draw_ctx);
  return status;
}
