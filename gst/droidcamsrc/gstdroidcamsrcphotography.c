/*
 * gst-droid
 *
 * Copyright (C) 2014 Mohammed Sameer <msameer@foolab.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "gstdroidcamsrcphotography.h"
#include "gstdroidcamsrc.h"
#include <stdlib.h>
#ifndef GST_USE_UNSTABLE_API
#define GST_USE_UNSTABLE_API
#endif /* GST_USE_UNSTABLE_API */
#include <gst/interfaces/photography.h>

GST_DEBUG_CATEGORY_EXTERN (gst_droidcamsrc_debug);
#define GST_CAT_DEFAULT gst_droidcamsrc_debug

enum EntryType
{
  TYPE_UINT,
  TYPE_ENUM,
  TYPE_FLOAT,
  TYPE_UNK,
};

struct Entry
{
  int prop;
  const gchar *photo_prop;
  enum EntryType type;
  const gchar *android_property;
};

struct Entry Entries[] = {
  /* enums */
  {PROP_WB_MODE, GST_PHOTOGRAPHY_PROP_WB_MODE, TYPE_ENUM, NULL},
  {PROP_COLOR_TONE, GST_PHOTOGRAPHY_PROP_COLOR_TONE, TYPE_ENUM, NULL},
  {PROP_SCENE_MODE, GST_PHOTOGRAPHY_PROP_SCENE_MODE, TYPE_ENUM, NULL},
  {PROP_FLASH_MODE, GST_PHOTOGRAPHY_PROP_FLASH_MODE, TYPE_ENUM, "flash-mode"},
  {PROP_FLICKER_MODE, GST_PHOTOGRAPHY_PROP_FLICKER_MODE, TYPE_ENUM, NULL},
  {PROP_FOCUS_MODE, GST_PHOTOGRAPHY_PROP_FOCUS_MODE, TYPE_ENUM, NULL},
  {PROP_EXPOSURE_MODE, GST_PHOTOGRAPHY_PROP_EXPOSURE_MODE, TYPE_ENUM, NULL},
  {PROP_NOISE_REDUCTION, GST_PHOTOGRAPHY_PROP_NOISE_REDUCTION, TYPE_ENUM, NULL},

  /* floats */
  {PROP_ZOOM, GST_PHOTOGRAPHY_PROP_ZOOM, TYPE_FLOAT, NULL},
  {PROP_EV_COMP, GST_PHOTOGRAPHY_PROP_EV_COMP, TYPE_FLOAT, NULL},
  {PROP_ANALOG_GAIN, GST_PHOTOGRAPHY_PROP_ANALOG_GAIN, TYPE_FLOAT, NULL},
  {PROP_LENS_FOCUS, GST_PHOTOGRAPHY_PROP_LENS_FOCUS, TYPE_FLOAT, NULL},

  /* unsigned ints */
  {PROP_APERTURE, GST_PHOTOGRAPHY_PROP_APERTURE, TYPE_UINT, NULL},
  {PROP_ISO_SPEED, GST_PHOTOGRAPHY_PROP_ISO_SPEED, TYPE_UINT, NULL},
  {PROP_COLOR_TEMPERATURE, GST_PHOTOGRAPHY_PROP_COLOR_TEMPERATURE, TYPE_UINT,
      NULL},
  {PROP_MIN_EXPOSURE_TIME, GST_PHOTOGRAPHY_PROP_MIN_EXPOSURE_TIME, TYPE_UINT,
      NULL},
  {PROP_MAX_EXPOSURE_TIME, GST_PHOTOGRAPHY_PROP_MAX_EXPOSURE_TIME, TYPE_UINT,
      NULL},

  /* unsigned int32 */
  {PROP_EXPOSURE_TIME, GST_PHOTOGRAPHY_PROP_EXPOSURE_TIME, TYPE_UINT, NULL},

  /* unknown */
  {PROP_CAPABILITIES, GST_PHOTOGRAPHY_PROP_CAPABILITIES, TYPE_UNK, NULL},
  {PROP_IMAGE_CAPTURE_SUPPORTED_CAPS,
      GST_PHOTOGRAPHY_PROP_IMAGE_CAPTURE_SUPPORTED_CAPS, TYPE_UNK, NULL},
  {PROP_IMAGE_PREVIEW_SUPPORTED_CAPS,
      GST_PHOTOGRAPHY_PROP_IMAGE_PREVIEW_SUPPORTED_CAPS, TYPE_UNK, NULL},
  {PROP_WHITE_POINT, GST_PHOTOGRAPHY_PROP_WHITE_POINT, TYPE_UNK, NULL},
};

struct PhotoEntry
{
  enum EntryType type;
  union
  {
    int ival;
    uint uval;
    float fval;
  };

  GHashTable *map;
};

struct _GstDroidCamSrcPhotography
{
  struct PhotoEntry entries[PROP_PHOTO_MAX - 1];
};

void
gst_droidcamsrc_photography_register (gpointer g_iface, gpointer iface_data)
{
  // TODO:

}

void
gst_droidcamsrc_photography_add_overrides (GObjectClass * klass)
{
  int x;
  int len = G_N_ELEMENTS (Entries);

  for (x = 0; x < len; x++) {
    g_object_class_override_property (klass, Entries[x].prop,
        Entries[x].photo_prop);
  }
}

gboolean
gst_droidcamsrc_photography_get_property (GstDroidCamSrc * src, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  switch (prop_id) {
    case PROP_WB_MODE:
    case PROP_COLOR_TONE:
    case PROP_SCENE_MODE:
    case PROP_FLASH_MODE:
    case PROP_FLICKER_MODE:
    case PROP_FOCUS_MODE:
    case PROP_NOISE_REDUCTION:
    case PROP_EXPOSURE_MODE:
      g_value_set_enum (value, src->photo->entries[prop_id - 1].ival);
      return TRUE;

    case PROP_ZOOM:
    case PROP_EV_COMP:
    case PROP_ANALOG_GAIN:
    case PROP_LENS_FOCUS:
      g_value_set_float (value, src->photo->entries[prop_id - 1].fval);
      return TRUE;

    case PROP_APERTURE:
    case PROP_ISO_SPEED:
    case PROP_COLOR_TEMPERATURE:
    case PROP_MIN_EXPOSURE_TIME:
    case PROP_MAX_EXPOSURE_TIME:
    case PROP_EXPOSURE_TIME:
      g_value_set_uint (value, src->photo->entries[prop_id - 1].uval);
      return TRUE;

    case PROP_CAPABILITIES:
    case PROP_IMAGE_CAPTURE_SUPPORTED_CAPS:
    case PROP_IMAGE_PREVIEW_SUPPORTED_CAPS:
    case PROP_WHITE_POINT:
      // TODO:

      return TRUE;
  }

  return FALSE;
}

gboolean
gst_droidcamsrc_photography_set_property (GstDroidCamSrc * src, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  // TODO:

  switch (prop_id) {
    case PROP_WB_MODE:
    case PROP_COLOR_TONE:
    case PROP_SCENE_MODE:
    case PROP_FLASH_MODE:
    case PROP_FLICKER_MODE:
    case PROP_FOCUS_MODE:
    case PROP_EV_COMP:
    case PROP_ISO_SPEED:
    case PROP_APERTURE:
    case PROP_EXPOSURE_TIME:
    case PROP_ZOOM:
    case PROP_COLOR_TEMPERATURE:
    case PROP_WHITE_POINT:
    case PROP_ANALOG_GAIN:
    case PROP_LENS_FOCUS:
    case PROP_MIN_EXPOSURE_TIME:
    case PROP_MAX_EXPOSURE_TIME:
    case PROP_NOISE_REDUCTION:
    case PROP_EXPOSURE_MODE:
      return TRUE;
  }

  return FALSE;
}

void
gst_droidcamsrc_photography_init (GstDroidCamSrc * src)
{
  int x;
  GKeyFile *file = g_key_file_new ();
  int len = G_N_ELEMENTS (Entries);
  gchar *file_path =
      g_build_path ("/", SYSCONFDIR, "gst-droid/gstdroidcamsrc.conf", NULL);

  if (!g_key_file_load_from_file (file, file_path, G_KEY_FILE_NONE, NULL)) {
    GST_WARNING ("failed to load configuration file %s", file_path);
  }

  src->photo = g_slice_new0 (GstDroidCamSrcPhotography);

  for (x = 0; x < len; x++) {
    int prop_id = Entries[x].prop - 1;
    src->photo->entries[prop_id].type = Entries[x].type;

    if (Entries[x].android_property) {
      gchar **keys;
      gsize len;
      /* TODO: load and populate the map */
      src->photo->entries[prop_id].map =
          g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, g_free);

      keys = g_key_file_get_keys (file, Entries[x].photo_prop, &len, NULL);
      if (!keys) {
        GST_WARNING ("failed to load %s", Entries[x].photo_prop);
      } else {
        int y;
        for (y = 0; y < len; y++) {
          gchar *val =
              g_key_file_get_value (file, Entries[x].photo_prop, keys[y], NULL);
          if (val) {
            GST_LOG ("loaded %s: %s = %s", Entries[x].photo_prop, keys[y], val);
            int key = atoi (keys[y]);
            g_hash_table_insert (src->photo->entries[prop_id].map,
                GINT_TO_POINTER (key), val);
          } else {
            GST_WARNING ("failed to load %s: %s", Entries[x].photo_prop,
                keys[y]);
          }
        }

        g_strfreev (keys);
      }
    } else {
      src->photo->entries[prop_id].map = NULL;
    }
  }

  src->photo->entries[PROP_WB_MODE - 1].ival = GST_PHOTOGRAPHY_WB_MODE_AUTO;
  src->photo->entries[PROP_COLOR_TONE - 1].ival =
      GST_PHOTOGRAPHY_COLOR_TONE_MODE_NORMAL;
  src->photo->entries[PROP_SCENE_MODE - 1].ival =
      GST_PHOTOGRAPHY_SCENE_MODE_AUTO;
  src->photo->entries[PROP_FLASH_MODE - 1].ival =
      GST_PHOTOGRAPHY_FLASH_MODE_AUTO;
  src->photo->entries[PROP_FLICKER_MODE - 1].ival =
      GST_PHOTOGRAPHY_FLICKER_REDUCTION_OFF;
  src->photo->entries[PROP_FOCUS_MODE - 1].ival =
      GST_PHOTOGRAPHY_FOCUS_MODE_CONTINUOUS_NORMAL;
  src->photo->entries[PROP_NOISE_REDUCTION - 1].ival = 0;       /* TODO: is that correct? */
  src->photo->entries[PROP_EXPOSURE_MODE - 1].ival =
      GST_PHOTOGRAPHY_EXPOSURE_MODE_AUTO;

  src->photo->entries[PROP_ZOOM - 1].fval = 1.0;
  src->photo->entries[PROP_EV_COMP - 1].fval = 0.0;
  src->photo->entries[PROP_ANALOG_GAIN - 1].fval = 0.0; /* TODO: is that correct? */
  src->photo->entries[PROP_LENS_FOCUS - 1].fval = 0.0;  /* TODO: is that correct? */

  src->photo->entries[PROP_APERTURE - 1].uval = 0;
  src->photo->entries[PROP_ISO_SPEED - 1].uval = 0;
  src->photo->entries[PROP_COLOR_TEMPERATURE - 1].uval = 0;     /* TODO: is that correct? */
  src->photo->entries[PROP_MIN_EXPOSURE_TIME - 1].uval = 0;     /* TODO: is that correct? */
  src->photo->entries[PROP_MAX_EXPOSURE_TIME - 1].uval = 0;     /* TODO: is that correct? */
  src->photo->entries[PROP_EXPOSURE_TIME - 1].uval = 0; /* TODO: is that correct? */

  /* TODO: we handle those manually */
  /*
   * src->photo->entries[PROP_CAPABILITIES - 1];
   * src->photo->entries[PROP_IMAGE_CAPTURE_SUPPORTED_CAPS - 1];
   * src->photo->entries[PROP_IMAGE_PREVIEW_SUPPORTED_CAPS - 1];
   * src->photo->entries[PROP_WHITE_POINT - 1];
   */

  g_free (file_path);
  g_key_file_unref (file);
}

void
gst_droidcamsrc_photography_destroy (GstDroidCamSrc * src)
{
  int x;
  int len = G_N_ELEMENTS (Entries);

  for (x = 0; x < len; x++) {
    int prop_id = Entries[x].prop - 1;
    if (src->photo->entries[prop_id].map) {
      g_hash_table_unref (src->photo->entries[prop_id].map);
      src->photo->entries[prop_id].map = NULL;
    }
  }

  g_slice_free (GstDroidCamSrcPhotography, src->photo);
  src->photo = NULL;
}
