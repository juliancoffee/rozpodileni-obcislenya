#include "globals.h"
#include "gui.h"

struct GlobalData global_data = {
    .pixels = 0,
    .palette = {.data = NULL, .len = 0},
    .set = NULL,
    .surface = NULL,
    .is_sync = true,
    .num_threads = 4,
};

// TODO: increase and decrease number of threads
// TODO: implement pausing
// TODO: implement clearing of image
int main(int argc, char **argv) {
  char *img_size_request = getenv("IMV_SIZE");
  if (img_size_request != NULL) {
    global_data.pixels = atoi(img_size_request);
  } else {
    global_data.pixels = 500;
  }
  int status = start_app(argc, argv);
  return status;
}
