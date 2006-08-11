#include <gtk/gtk.h>

#include "private.h"
#include "preview.h"


void
avs3_preview_draw (Avs3_Data *data, gint frame_nbr)
{
  GdkPixbuf           *pixbuf;
  AVS_Clip            *clip_rgb32;
  AVS_VideoInfo       *info;
  AVS_ColorSpace      *csp;
  AVS_VideoFrame      *frame;
  ColorSpace_Id        csp_id;
  guint                width;
  guint                height;
  const unsigned char *rgb;

  info = avs_clip_videoinfo_get (data->clip);
  csp = avs_videoinfo_colorspace_get (info);
  csp_id = avs_colorspace_id_get (csp);
  avs_colorspace_delete (csp);
  avs_videoinfo_delete (info);

  if (csp_id == I_RGB32)
    clip_rgb32 = data->clip;
  else
    clip_rgb32 = avs_clip_new_to_rgb32 (data->clip);

  frame = avs_clip_videoframe_get (clip_rgb32, frame_nbr);
  width = avs_videoframe_width_get (frame);
  height = avs_videoframe_height_get (frame);
  rgb = avs_videoframe_plane_get (frame, '~');
  g_print ("size (preview) : %dx%d  %d\n", width, height, sizeof (*rgb));

  gtk_widget_set_size_request (data->preview, (gint)width, (gint)height);
  pixbuf = gdk_pixbuf_new_from_data (rgb,
				     GDK_COLORSPACE_RGB, TRUE,
				     8, (gint)width, (gint)height, 4 * (gint)width,
				     (GdkPixbufDestroyNotify) g_free,
				     NULL);
  gtk_image_set_from_pixbuf (GTK_IMAGE (data->preview), pixbuf);

  avs_videoframe_delete (frame);
  if (csp_id != I_RGB32)
    avs_clip_delete (clip_rgb32);
}
