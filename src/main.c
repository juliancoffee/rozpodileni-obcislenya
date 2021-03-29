#include "gui.h"
#include "globals.h"

struct GlobalData global_data = {
    .pixels = 0,
    .palette = {.data = NULL, .len = 0},
};

int main(int argc, char **argv) {
  global_data.pixels = atoi(getenv("IMG_SIZE"));
  int status = start_app(argc, argv);
  return status;
}
