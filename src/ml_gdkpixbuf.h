/* $Id: ml_gdkpixbuf.h,v 1.3 2004/06/28 21:51:59 oandrieu Exp $ */

#define GdkPixbuf_val(val)       (check_cast(GDK_PIXBUF, val))
#define Val_GdkPixbuf(val)       (Val_GObject(G_OBJECT(val)))
#define Val_GdkPixbuf_new(val)   (Val_GObject_new(G_OBJECT(val)))

