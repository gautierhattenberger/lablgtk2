/* $Id: ml_gdkpixbuf.h,v 1.2 2003/02/20 06:47:53 garrigue Exp $ */

#define GdkPixbuf_val(val) ((GdkPixbuf*)GObject_val(val))
#define Val_GdkPixbuf(val) (Val_GObject((GObject*)(val)))
