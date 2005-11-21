/* $Id: ml_gtk.h,v 1.13 2005/10/17 11:52:03 garrigue Exp $ */

/* GObjects */

#define Val_GtkAccelGroup(val) (Val_GObject(&val->parent))
#define Val_GtkStyle(val) (Val_GObject(&val->parent_instance))

#define GtkAccelGroup_val(val) check_cast(GTK_ACCEL_GROUP,val)
#define GtkStyle_val(val) check_cast(GTK_STYLE,val)

/* GtkObjects */
CAMLexport value Val_GtkObject_sink (GtkObject *w);

#define Val_GtkAny(w) (Val_GObject((GObject*)w))
#define Val_GtkAny_sink(w) (Val_GtkObject_sink(GTK_OBJECT(w)))
#define Val_GtkWidget Val_GtkAny
#define Val_GtkWidget_sink Val_GtkAny_sink

/* For GList containing widgets */
CAMLexport value Val_GtkWidget_func(gpointer w);

#define GtkObject_val(val) check_cast(GTK_OBJECT,val)
#define GtkWidget_val(val) check_cast(GTK_WIDGET,val)
#define GtkAdjustment_val(val) check_cast(GTK_ADJUSTMENT,val)
#define GtkItem_val(val) check_cast(GTK_ITEM,val)
#define GtkTooltips_val(val) check_cast(GTK_TOOLTIPS,val)

#define GtkClipboard_val(val) ((GtkClipboard*)Pointer_val(val))
