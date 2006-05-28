#include <gtk/gtk.h>

#include "private.h"
#include "menu.h"


/* Callbacks */
static gboolean _delete_window_cb    (GtkWidget *widget,
                                      GdkEvent  *event,
                                      gpointer   user_data);
static void     _destroy_window_cb   (GtkObject *widget,
                                      gpointer   user_data);

/* Code */
void
avs3_main_window ()
{
  Avs3_Data *data;
  GtkWidget *vbox;
  GtkWidget *menu;

  data = (Avs3_Data *)g_malloc0 (sizeof (Avs3_Data));
  if (!data) return;

  data->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (data->window), "Avisynth 3.0 Test Application");
  g_signal_connect (G_OBJECT (data->window),
                    "delete-event",
                    G_CALLBACK (_delete_window_cb),
                    data);
  g_signal_connect (G_OBJECT (data->window),
                    "destroy",
                    G_CALLBACK (_destroy_window_cb),
                    data);

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (data->window), vbox);
  gtk_widget_show (vbox);

  menu = avs3_menu (data);
  gtk_box_pack_start (GTK_BOX (vbox), menu, FALSE, TRUE, 0);
  gtk_widget_show (menu);

  data->preview = gtk_image_new ();
  gtk_widget_set_size_request (data->preview, 320, 240);
  gtk_box_pack_start (GTK_BOX (vbox), data->preview, FALSE, TRUE, 0);
  gtk_widget_show (data->preview);

  data->scale = gtk_hscale_new_with_range (0.0, 1.0, 1.0);
  gtk_scale_set_digits (GTK_SCALE (data->scale), 0);
  gtk_scale_set_value_pos (GTK_SCALE (data->scale), GTK_POS_RIGHT);
  gtk_box_pack_start (GTK_BOX (vbox), data->scale, FALSE, TRUE, 0);
  gtk_widget_show (data->scale);

  data->status = gtk_statusbar_new ();
  gtk_box_pack_start (GTK_BOX (vbox), data->status, FALSE, TRUE, 0);
  gtk_widget_show (data->status);

  gtk_widget_show (data->window);
}

void
_data_delete (Avs3_Data *data)
{
  if (data->filename)
    g_free (data->filename);
  if (data->clip)
    avs_clip_delete (data->clip);
  if (data->env)
    avs_environment_delete (data->env);

  g_free (data);
}

static gboolean
_delete_window_cb (GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   user_data)
{
  gtk_main_quit ();
  
  _data_delete ((Avs3_Data *)user_data);

  return TRUE;
}
static void
_destroy_window_cb (GtkObject *widget,
                    gpointer   user_data)
{
  gtk_main_quit ();

  _data_delete ((Avs3_Data *)user_data);
}
