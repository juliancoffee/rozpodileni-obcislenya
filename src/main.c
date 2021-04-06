#include "data.h"
#include "gui.h"
#include "memmacros.h"


// TODO: implement pausing
// TODO: implement clearing of image
int main(int argc, char **argv) {

  struct computation_context_t comp_ctx = {
      .is_sync = true,
      .num_threads = 4,
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

  char *img_size_request = getenv("IMG_SIZE");

  if (img_size_request != NULL) {
    global_data.comp_ctx->pixels = atoi(img_size_request);
  } else {
    global_data.comp_ctx->pixels = 500;
  }
  int status = start_app(argc, argv, &global_data);
  free(global_data.draw_ctx->palette.data);
  free(global_data.comp_ctx);
  free(global_data.draw_ctx);
  return status;
}
