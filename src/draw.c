#include "draw.h"
#include "globals.h"
#include "util.h"
#include <assert.h>
#include <gtk/gtk.h>

extern struct GlobalData global_data;

// input: ratio is between 0 to 1
// output: rgb color
static void set_rgb(double ratio, double *red, double *green, double *blue) {
  // we want to normalize ratio so that it fits in to 6 regions
  // where each region is 256 units long
  int normalized = (int)(ratio * 256 * 6);

  // find the distance to the start of the closest region
  double x = (double)(normalized % 256) / 256;

  *red = 0;
  *green = 0;
  *blue = 0;
  switch (normalized / 256) {
  case 0:
    *red = 1;
    *green = x;
    *blue = 0;
    break; // red
  case 1:
    *red = 1 - x;
    *green = 1;
    *blue = 0;
    break; // yellow
  case 2:
    *red = 0;
    *green = 1;
    *blue = x;
    break; // green
  case 3:
    *red = 0;
    *green = 1 - x;
    *blue = 1;
    break; // cyan
  case 4:
    *red = x;
    *green = 0;
    *blue = 1;
    break; // blue
  case 5:
    *red = 1;
    *green = 0;
    *blue = 1 - x;
    break; // magenta
  }
}

void init_palette(struct Palette *palette) {
  const size_t num_colors = NUM_COLORS;
  palette->data = (struct RGB *)malloc(sizeof(struct RGB) * num_colors);
  palette->len = num_colors;
  for (size_t color = 0; color < num_colors; color++) {
    float colorf = (float)color;
    set_rgb(colorf / num_colors, &palette->data[color].red,
            &palette->data[color].green, &palette->data[color].blue);
  }
}

// input: int color from 0 to NUM_COLORS
static void set_colors_from(size_t color, double *red, double *green,
                            double *blue) {
  assert(color < global_data.palette.len);
  *red = global_data.palette.data[color - 1].red;
  *green = global_data.palette.data[color - 1].green;
  *blue = global_data.palette.data[color - 1].blue;
}

int draw_square(cairo_t *cr, atomic_int *colors, size_t size) {
  if (global_data.palette.data == NULL) {
    init_palette(&global_data.palette);
  }
  if (colors == NULL) {
    g_message("Wait a minute, this is not democracy. This is anal sex.\n");
    return -1;
  }
  for (size_t x = 0; x < size; x++) {
    for (size_t y = 0; y < size; y++) {
      double red = 0;
      double green = 0;
      double blue = 0;
      atomic_int *color = element_at(colors, x, y, size);
      set_colors_from(*color, &red, &green, &blue);
      cairo_set_source_rgb(cr, red, green, blue);
      cairo_rectangle(cr, x, y, 1, 1);
      cairo_fill(cr);
    }
  }
  cairo_destroy(cr);
  return 0;
}
