/* $Id: ml_gdkpixbuf.h,v 1.5 2005/05/03 20:50:21 oandrieu Exp $ */

#define GdkPixbuf_val(val)       (check_cast(GDK_PIXBUF, val))
value Val_GdkPixbuf_ (GdkPixbuf *, gboolean);
#define Val_GdkPixbuf(p)         Val_GdkPixbuf_(p, FALSE)
#define Val_GdkPixbuf_new(p)     Val_GdkPixbuf_(p, TRUE)
