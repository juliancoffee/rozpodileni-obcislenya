#include "data.h"
#include "gui.h"
#include "memmacros.h"

// TODO: implement pausing
// TODO: implement clearing of image
int main(int argc, char **argv) {
  char *img_size_request = getenv("IMG_SIZE");
  size_t pixels;
  if (img_size_request != NULL) {
    pixels = atoi(img_size_request);
  } else {
    pixels = 500;
  }

  struct computation_context_t comp_ctx = {
      .is_sync = true,
      .num_threads = 4,
      .workers = calloc(4, sizeof(pthread_t)),
      .pixels = pixels,
      .is_paused = BOXED((bool) false),
      .set = NULL,
  };

  struct drawing_context_t draw_ctx = {
      .palette = {.data = NULL, .len = 0},
      .surface = NULL,
  };

  struct GlobalData global_data = {
      .comp_ctx = BOXED(comp_ctx),
      .draw_ctx = BOXED(draw_ctx),
  };

  int status = start_app(argc, argv, &global_data);
  free(global_data.draw_ctx->palette.data);
  free(global_data.comp_ctx->workers);
  free(global_data.comp_ctx);
  free(global_data.draw_ctx);
  return status;
}
