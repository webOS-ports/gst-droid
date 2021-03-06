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

#ifndef __GST_GRALLOC_H__
#define __GST_GRALLOC_H__

#include <gst/gst.h>
#include <gst/video/video.h>

G_BEGIN_DECLS

#define GST_ALLOCATOR_GRALLOC                   "gralloc"
#define GST_CAPS_FEATURE_MEMORY_DROID_HANDLE    "memory:DroidHandle"

typedef enum {
  /* buffer is never read in software */
  GST_GRALLOC_USAGE_SW_READ_NEVER         = 0x00000000,
  /* buffer is rarely read in software */
  GST_GRALLOC_USAGE_SW_READ_RARELY        = 0x00000002,
  /* buffer is often read in software */
  GST_GRALLOC_USAGE_SW_READ_OFTEN         = 0x00000003,
  /* mask for the software read values */
  GST_GRALLOC_USAGE_SW_READ_MASK          = 0x0000000F,

  /* buffer is never written in software */
  GST_GRALLOC_USAGE_SW_WRITE_NEVER        = 0x00000000,
  /* buffer is never written in software */
  GST_GRALLOC_USAGE_SW_WRITE_RARELY       = 0x00000020,
  /* buffer is never written in software */
  GST_GRALLOC_USAGE_SW_WRITE_OFTEN        = 0x00000030,
  /* mask for the software write values */
  GST_GRALLOC_USAGE_SW_WRITE_MASK         = 0x000000F0,

  /* buffer will be used as an OpenGL ES texture */
  GST_GRALLOC_USAGE_HW_TEXTURE            = 0x00000100,
  /* buffer will be used as an OpenGL ES render target */
  GST_GRALLOC_USAGE_HW_RENDER             = 0x00000200,
  /* buffer will be used by the 2D hardware blitter */
  GST_GRALLOC_USAGE_HW_2D                 = 0x00000400,
  /* buffer will be used by the HWComposer HAL module */
  GST_GRALLOC_USAGE_HW_COMPOSER           = 0x00000800,
  /* buffer will be used with the framebuffer device */
  GST_GRALLOC_USAGE_HW_FB                 = 0x00001000,
  /* buffer will be used with the HW video encoder */
  GST_GRALLOC_USAGE_HW_VIDEO_ENCODER      = 0x00010000,
  /* mask for the software usage bit-mask */
  GST_GRALLOC_USAGE_HW_MASK               = 0x00011F00,
} GstGrallocUsage;

GstAllocator * gst_gralloc_allocator_new (void);

GstMemory    * gst_gralloc_allocator_alloc (GstAllocator * allocator, gint width, gint height,
					    int format, int usage);

gboolean       gst_is_gralloc_memory (GstMemory * mem);

GstMemory    * gst_gralloc_allocator_wrap (GstAllocator * allocator, gint width, gint height,
					   int usage, guint8 * data,
					   gsize size, int hal_format);

// TODO: use GstContext to wrap this android specific struct
struct ANativeWindowBuffer * gst_memory_get_native_buffer (GstMemory *mem);
GstMemory *gst_memory_from_native_buffer(struct ANativeWindowBuffer * buffer);

G_END_DECLS

#endif /* __GST_GRALLOC_H__ */
