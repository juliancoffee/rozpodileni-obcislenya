#include "data.h"
#include "gui.h"
#include "memmacros.h"

#define DEFAULT_THREADS 4
// TODO: implement clearing of image
int main(int argc, char **argv) {
  /* set image size */
  char *img_size_request = getenv("IMG_SIZE");
  size_t pixels;
  if (img_size_request != NULL) {
    pixels = (size_t) abs(atoi(img_size_request));
  } else {
    pixels = 500;
  }

  /* Initialize workers */
  struct worker_t *workers = malloc_or_die(
      DEFAULT_THREADS * sizeof(struct worker_t), "allocating workers");
  for (size_t n = 0; n < DEFAULT_THREADS; n++) {
    workers[n].is_init = false;
  }

  struct computation_context_t comp_ctx = {
      .pixels = pixels,
      .set = NULL,
      .is_sync = true,
      .is_paused = BOXED((bool) false),
      .num_threads = DEFAULT_THREADS,
      .workers = workers,
  };

  struct drawing_context_t draw_ctx = {
      .palette = {.data = NULL, .len = 0},
      .surface = NULL,
  };

  struct GlobalData global_data = {
      .comp_ctx = BOXED(comp_ctx),
      .draw_ctx = BOXED(draw_ctx),
  };

  int status = start_gui(argc, argv, &global_data);
  free(global_data.draw_ctx->palette.data);
  free(global_data.comp_ctx->workers);
  free(global_data.comp_ctx);
  free(global_data.draw_ctx);
  return status;
}
