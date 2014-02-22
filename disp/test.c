#include <gtk/gtk.h>

GtkWidget * createWindow(int w, int h){
	
	GtkWidget *new_window;
	
	new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(new_window);
	
	gtk_window_set_title(GTK_WINDOW(new_window), "Center");
	gtk_window_set_default_size(GTK_WINDOW(new_window), w, h);
	gtk_window_set_position(GTK_WINDOW(new_window), GTK_WIN_POS_CENTER);
	gtk_widget_show(new_window);

	g_signal_connect_swapped(G_OBJECT(new_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	return new_window;
}

int main( int argc, char *argv[])
{
	int useless = 0;
  GtkWidget *window;
  
  gtk_init(&argc, &argv);

  window = createWindow(200, 200);
  
	gtk_main();

  return 0;
}
