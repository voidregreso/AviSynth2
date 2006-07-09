/* Avisynth 3.0 C Interface
 * Copyright 2006 Vincent Torri <vtorri at univ-evry dot fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA, or visit
 * http://www.gnu.org/copyleft/gpl.html .
 *
 * As a special exception, I give you permission to link to the
 * Avisynth C interface with independent modules that communicate with
 * the Avisynth C interface solely through the interfaces defined in
 * avisynth_c.h, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting combined work
 * under terms of your choice, provided that every copy of the
 * combined work is accompanied by a complete copy of the source code
 * of the Avisynth C interface and Avisynth itself (with the version
 * used to produce the combined work), being distributed under the
 * terms of the GNU General Public License plus this exception.  An
 * independent module is a module which is not derived from or based
 * on Avisynth C Interface, such as 3rd-party filters, import and
 * export plugins, or graphical user interfaces.
 */

#ifndef __CLIP_C_H__
#define __CLIP_C_H__


/* C API include */
#include "define_c.h"
#include "videoinfo_c.h"
#include "videoframe_c.h"
#include "runtime_environment_c.h"


/** \file clip_c.h
 * \brief C interface for clips
 *
 * C interface for clips. It allows to create clips from scripts,
 * files or other clips. You can get video informations and video
 * frames data (in raw format) from that interface.
 *
 * An example of Avisynth script is:

 * \code
 * GstreamerSource("file.mkv", 0, 0)
 * \endcode
 *
 * This script will load the file @em file.mkv in Avisynth using
 * Gstreamer.
 *
 * @li If this script is in a file, then use avs_clip_new_from_file().
 * @li If this script is in a string, then use avs_clip_new_from_script().
 *
 * You can convert a clip from its current color space to another with
 * the functions avs_clip_new_to_yv12() and avs_clip_new_to_rgb32().
 *
 * You can retrieve frame of a clip with the function
 * avs_clip_videoframe_get(). It is in raw format (that is, it is not
 * compressed).
 *
 * You can retrieve the informations of a clip with the function
 * avs_clip_videoinfo_get().
 *
 * Once you have finished to use an #AVS_Clip, free it with
 * avs_clip_delete().
 */


/**
 * opaque declaration of a clip
 */
typedef struct AVS_Clip_ AVS_Clip;


/** \brief Create a clip from a script.
 *
 * \param script The string that contains the script.
 * \param p_env A pointer to an AVS_Environment pointer.
 * \return A newly allocated clip.
 *
 * Create a clip from a script, as a string (char *). The environment
 * is set by \p p_env. If an error
 * occurred, the returned value is \c NULL. Otherwise, it is a valid
 * clip.
 */
AVS_C_API AVS_Clip *avs_clip_new_from_script (const char *script, const AVS_Environment *p_env);


/** \brief Create a clip from a file.
 *
 * \param filename The string of the file that contains the script.
 * \param p_env A pointer to an AVS_Environment pointer.
 * \return A newly allocated clip.
 *
 * Create a clip from a file. The environment is set by \p p_env. If
 * an error occurred, the returned value is \c NULL. Otherwise, it is
 * a valid clip.
 */
AVS_C_API AVS_Clip *avs_clip_new_from_file   (const char *filename, const AVS_Environment *p_env);


/** \brief Convert a clip to a newly allocated RGB32 clip.
 *
 * \param p_clip The clip to convert to RGB32 colorspace.
 * \return A newly allocated clip in RGB32 colorspace.
 *
 * Convert the clip \p p_clip to a newly allocated RGB32 clip. If \p
 * p_clip is already in RGB32, then \c NULL is returned. If an error
 * occurred, the returned value is \c NULL.
 */
AVS_C_API AVS_Clip *avs_clip_new_to_rgb32    (const AVS_Clip *p_clip);


/** \brief Convert a clip to a newly allocated YV12 clip.
 *
 * \param p_clip The clip to convert to YV12 colorspace.
 * \return A newly allocated clip in YV12 colorspace.
 *
 * Convert the clip \p p_clip to a newly allocated YV12 clip. If \p
 * p_clip is already in YV12, then \c NULL is returned. If an error
 * occurred, the returned value is \c NULL.
 */
AVS_C_API AVS_Clip *avs_clip_new_to_yv12     (const AVS_Clip *p_clip);


/** \brief Delete a clip.
 *
 * \param p_clip The clip to delete.
 *
 * Delete the clip \p p_clip.
 */
AVS_C_API void      avs_clip_delete          (AVS_Clip *p_clip);


/** \brief Retrieve the video informations of a clip.
 *
 * \param p_clip The clip to retrieve informations from.
 * \return A newly allocated AVS_VideoInfo structure.
 *
 * Retrieve the video information of the clip \p p_clip. If \p p_clip
 * is \c NULL, the returned value is \c NULL. The returned value must
 * be free with avs_videoinfo_delete().
 */
AVS_C_API AVS_VideoInfo *avs_clip_videoinfo_get (const AVS_Clip *p_clip);


/** \brief Retrieve the video frame of a clip.
 *
 * \param p_clip The clip to retrieve informations from.
 * \param n The frame number.
 * \return A newly allocated AVS_VideoFrame structure.
 *
 * Retrieve the video frame number \p n of the clip \p p_clip. If \p
 * p_clip is \c NULL, the returned value is \c NULL. The returned
 * value must be free with avs_videoframe_delete().
 */
AVS_C_API AVS_VideoFrame *avs_clip_videoframe_get (const AVS_Clip *p_clip, long int n);


#endif /* __CLIP_C_H__ */
