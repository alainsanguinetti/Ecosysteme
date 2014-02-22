#include <gtk/gtk.h>

int main (int argc, char **argv)
{
  GtkWidget     *win, *but;

  gtk_init( &argc, &argv );

  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (win, "delete-event", G_CALLBACK (gtk_true), NULL);
  g_signal_connect (win, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  but = gtk_button_new_with_label ("Close yourself. I mean it!");
  g_signal_connect_swapped (but, "clicked", G_CALLBACK (gtk_object_destroy), win);
  gtk_container_add (GTK_CONTAINER (win), but);

  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
