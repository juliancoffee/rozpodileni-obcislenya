#include "controls.h"
#include "draw.h"
#include "globals.h"
#include "util.h"
#include <gtk/gtk.h>

static cairo_surface_t *surface = NULL;
extern struct GlobalData global_data;

static void clear_surface(void) {
  cairo_t *cr;
  cr = cairo_create(surface);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);
  cairo_destroy(cr);
}

static gboolean draw_cb(GtkWidget *_widget, cairo_t *cr, gpointer _data) {
  g_message("DRAW\n");
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);

  return FALSE;
}

static gboolean configure_cb(GtkWidget *widget, GdkEventConfigure *event,
                             gpointer _data) {
  g_message("CONFIGURE\n");
  if (surface != NULL) {
    cairo_surface_destroy(surface);
  }

  surface = gdk_window_create_similar_surface(
      gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR,
      gtk_widget_get_allocated_width(widget),
      gtk_widget_get_allocated_height(widget));

  clear_surface();
  global_data.surface = surface;
  return TRUE;
}

static void activate(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);

  gtk_window_set_title(GTK_WINDOW(window), "Mandelbrot Set Draw");

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_container_add(GTK_CONTAINER(window), box);

  GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_button_box_set_layout((GtkButtonBox *)button_box, GTK_BUTTONBOX_SPREAD);
  gtk_container_add(GTK_CONTAINER(box), button_box);

  GtkWidget *frame = gtk_frame_new(NULL);
  gtk_widget_set_size_request(frame, global_data.pixels, global_data.pixels);
  gtk_container_add(GTK_CONTAINER(box), frame);

  GtkWidget *drawing_area = gtk_drawing_area_new();
  g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), NULL);
  g_signal_connect(drawing_area, "configure-event", G_CALLBACK(configure_cb),
                   NULL);
  gtk_container_add(GTK_CONTAINER(frame), drawing_area);

  GtkWidget *button = gtk_button_new_with_label("Draw");
  g_signal_connect(button, "clicked", G_CALLBACK(on_draw_button), drawing_area);
  gtk_container_add(GTK_CONTAINER(button_box), button);

  GtkWidget *exit_button = gtk_button_new_with_label("Exit");
  g_signal_connect_swapped(exit_button, "clicked",
                           G_CALLBACK(gtk_widget_destroy), window);
  gtk_container_add(GTK_CONTAINER(button_box), exit_button);

  gtk_widget_show_all(window);
}

int start_app(int argc, char **argv) {
  GtkApplication *app = gtk_application_new("org.example.mandelbrot-draw",
                                            G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}
