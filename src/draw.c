#include "draw.h"
#include "util.h"
#include <assert.h>
#include <gtk/gtk.h>

// input: ratio is between 0 to 1
// output: rgb color
static void set_rgb(double ratio, double *red, double *green, double *blue) {
  // we want to normalize ratio so that it fits in to 6 regions
  // where each region is 256 units long
  int normalized = (int) (ratio * 256 * 6);

  // find the distance to the start of the closest region
  double x = (double) (normalized % 256) / 256;

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

static void init_palette(struct palette_t *palette) {
  const size_t num_colors = NUM_COLORS;
  struct rgb_tuple_t *palette_data = calloc_or_die(
      num_colors, sizeof(struct rgb_tuple_t), "allocating palette data");
  palette->data = palette_data;
  palette->len = num_colors;
  struct rgb_tuple_t *data = palette->data;
  for (size_t color = 0; color < num_colors; color++) {
    float colorf = (float) color;
    set_rgb(
        colorf / num_colors,
        &data[color].red,
        &data[color].green,
        &data[color].blue);
  }
}

// input: int color from 0 to NUM_COLORS
static void set_colors_from(
    size_t color,
    double *red,
    double *green,
    double *blue,
    struct palette_t palette) {
  assert(color < palette.len);
  struct rgb_tuple_t *data = palette.data;
  *red = data[color - 1].red;
  *green = data[color - 1].green;
  *blue = data[color - 1].blue;
}

/* Draw pixels from `colors` of `size` X `size` onto surface from `cr` context
 */
int draw_square(
    cairo_t *cr, atomic_int *colors, size_t size, struct palette_t palette) {
  if (palette.data == NULL) {
    init_palette(&palette);
  }
  if (colors == NULL) {
    g_warning("colors == NULL, set isn't initalized\n");
    return -1;
  }
  for (size_t x = 0; x < size; x++) {
    for (size_t y = 0; y < size; y++) {
      double red = 0;
      double green = 0;
      double blue = 0;
      atomic_int *color = element_at(colors, x, y, size);
      set_colors_from((size_t) *color, &red, &green, &blue, palette);
      cairo_set_source_rgb(cr, red, green, blue);
      cairo_rectangle(cr, (double) x, (double) y, 1, 1);
      cairo_fill(cr);
    }
  }
  cairo_destroy(cr);
  return 0;
}
