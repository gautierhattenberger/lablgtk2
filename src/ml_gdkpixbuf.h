/* $Id: ml_gdkpixbuf.h,v 1.4 2004/08/23 21:37:40 oandrieu Exp $ */

#define GdkPixbuf_val(val)       (check_cast(GDK_PIXBUF, val))
#define Val_GdkPixbuf(val)       Val_GAnyObject(val)
#define Val_GdkPixbuf_new(val)   Val_GAnyObject_new(val)
