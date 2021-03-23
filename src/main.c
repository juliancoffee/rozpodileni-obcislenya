#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello Mandelbrot\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(app);

  gtk_window_set_title(GTK_WINDOW(window), "Mandelbrot Set Draw");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

  GtkWidget *box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_button_box_set_layout((GtkButtonBox* )box, GTK_BUTTONBOX_SPREAD);
  gtk_container_add(GTK_CONTAINER(window), box);

  GtkWidget *button = gtk_button_new_with_label("Hello Mandel");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  gtk_container_add(GTK_CONTAINER(box), button);

  GtkWidget *exit_button = gtk_button_new_with_label("Exit");
  g_signal_connect_swapped(exit_button, "clicked",
                           G_CALLBACK(gtk_widget_destroy), window);
  gtk_container_add(GTK_CONTAINER(box), exit_button);

  gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new("org.example.mandelbrot-draw",
                                            G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
