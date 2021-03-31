#include "widgets.h"
#include "message.h"

GtkWidget *my_window(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Mandelbrot Set Draw");
  return window;
}

GtkWidget *my_box(GtkOrientation orientation) {
  GtkWidget *box = gtk_box_new(orientation, 5);
  return box;
}

GtkWidget *my_button_box(GtkOrientation orientation) {
  GtkWidget *button_box = gtk_button_box_new(orientation);
  gtk_button_box_set_layout((GtkButtonBox *)button_box, GTK_BUTTONBOX_SPREAD);
  return button_box;
}

GtkWidget *my_frame(size_t pixels) {
  GtkWidget *frame = gtk_frame_new(NULL);
  gtk_widget_set_size_request(frame, pixels, pixels);
  return frame;
}

GtkWidget *my_text_view(void) {
  GtkWidget *text_view = gtk_text_view_new();
  GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)text_view);
  char *msg_buf = info_text();
  gtk_text_buffer_set_text(buffer, msg_buf, -1);
  free(msg_buf);
  return text_view;
}
