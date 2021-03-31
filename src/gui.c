#include "gui.h"
#include "controls.h"
#include "globals.h"
#include "widgets.h"
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
  (void) _widget;
  (void) _data;
  g_message("DRAW\n");
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);

  return FALSE;
}

static gboolean
configure_cb(GtkWidget *widget, GdkEventConfigure *_event, gpointer _data) {
  (void) _event;
  (void) _data;
  g_message("CONFIGURE\n");
  if (surface != NULL) {
    cairo_surface_destroy(surface);
  }

  surface = gdk_window_create_similar_surface(
      gtk_widget_get_window(widget),
      CAIRO_CONTENT_COLOR,
      gtk_widget_get_allocated_width(widget),
      gtk_widget_get_allocated_height(widget));

  clear_surface();
  global_data.surface = surface;
  return TRUE;
}

static void activate(GtkApplication *app) {
  /* Widget creation */
  GtkWidget *window = my_window(app);

  GtkWidget *global_box = my_box(GTK_ORIENTATION_HORIZONTAL);

  GtkWidget *left_box = my_box(GTK_ORIENTATION_VERTICAL);
  GtkWidget *button_box = my_button_box(GTK_ORIENTATION_VERTICAL);
  GtkWidget *text_view = my_text_view();

  GtkWidget *draw_button = gtk_button_new_with_label("Draw");
  GtkWidget *calculate_button = gtk_button_new_with_label("Calculate");
  GtkWidget *sync_button = gtk_button_new_with_label("Sync");
  GtkWidget *async_button = gtk_button_new_with_label("Async");
  GtkWidget *exit_button = gtk_button_new_with_label("Exit");

  GtkWidget *frame = my_frame(global_data.comp_ctx->pixels);
  GtkWidget *drawing_area = gtk_drawing_area_new();

  /* Add elements to containers */
  gtk_container_add(GTK_CONTAINER(window), global_box);
  gtk_container_add(GTK_CONTAINER(global_box), left_box);
  gtk_container_add(GTK_CONTAINER(global_box), frame);
  gtk_container_add(GTK_CONTAINER(frame), drawing_area);
  gtk_container_add(GTK_CONTAINER(left_box), button_box);
  gtk_container_add(GTK_CONTAINER(button_box), draw_button);
  gtk_container_add(GTK_CONTAINER(button_box), calculate_button);
  gtk_container_add(GTK_CONTAINER(button_box), sync_button);
  gtk_container_add(GTK_CONTAINER(button_box), async_button);
  gtk_container_add(GTK_CONTAINER(button_box), exit_button);
  gtk_container_add(GTK_CONTAINER(left_box), text_view);

  /* Add signal callbacks */
  g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), NULL);
  g_signal_connect(
      drawing_area, "configure-event", G_CALLBACK(configure_cb), NULL);
  g_signal_connect_swapped(
      draw_button, "clicked", G_CALLBACK(draw_button_cb), drawing_area);

  g_signal_connect_swapped(
      calculate_button, "clicked", G_CALLBACK(compute_button_cb), global_data.comp_ctx);
  g_signal_connect_swapped(
      sync_button, "clicked", G_CALLBACK(sync_button_cb), text_view);
  g_signal_connect_swapped(
      async_button, "clicked", G_CALLBACK(async_button_cb), text_view);
  g_signal_connect_swapped(
      exit_button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

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
