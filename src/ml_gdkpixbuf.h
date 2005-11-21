/* $Id: ml_gdkpixbuf.h,v 1.6 2005/10/03 11:12:53 oandrieu Exp $ */

#define GdkPixbuf_val(val)       (check_cast(GDK_PIXBUF, val))
value Val_GdkPixbuf_ (GdkPixbuf *, gboolean);
#define Val_GdkPixbuf(p)         Val_GdkPixbuf_(p, TRUE)
#define Val_GdkPixbuf_new(p)     Val_GdkPixbuf_(p, FALSE)
