/* $Id: ml_gtkbin.c,v 1.9 2003/07/17 09:38:43 monate Exp $ */

#include <string.h>
#include <gtk/gtk.h>
#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/fail.h>

#include "wrappers.h"
#include "ml_glib.h"
#include "ml_gobject.h"
#include "ml_gdk.h"
#include "ml_gtk.h"
#include "gtk_tags.h"

/* Init all */

CAMLprim value ml_gtkbin_init(value unit)
{
    /* Since these are declared const, must force gcc to call them! */
    GType t =
        gtk_alignment_get_type() +
        gtk_event_box_get_type() +
        gtk_frame_get_type() +
        gtk_aspect_frame_get_type() +
        gtk_handle_box_get_type() +
        gtk_viewport_get_type() +
        gtk_scrolled_window_get_type() 
#ifndef _WIN32
        + gtk_socket_get_type()
#endif
;
    return Val_GType(t);
}

/* gtkalignment.h */
/*
#define GtkAlignment_val(val) check_cast(GTK_ALIGNMENT,val)
ML_4 (gtk_alignment_new, Float_val, Float_val, Float_val, Float_val,
      Val_GtkWidget_sink)
CAMLprim value ml_gtk_alignment_set (value x, value y,
                                     value xscale, value yscale, value val)
{
    GtkAlignment *alignment = GtkAlignment_val(val);
    gtk_alignment_set (alignment,
		       Option_val(x, Float_val, alignment->xalign),
		       Option_val(y, Float_val, alignment->yalign),
		       Option_val(xscale, Float_val, alignment->xscale),
		       Option_val(yscale, Float_val, alignment->xscale));
    return Val_unit;
}
*/

/* gtkeventbox.h */

/* gtkframe.h */

/* gtkaspectframe.h */
/*
#define GtkAspectFrame_val(val) check_cast(GTK_ASPECT_FRAME,val)
ML_5 (gtk_aspect_frame_new, Optstring_val,
      Float_val, Float_val, Float_val, Bool_val, Val_GtkWidget_sink)
ML_5 (gtk_aspect_frame_set, GtkAspectFrame_val, Float_val, Float_val,
      Float_val, Bool_val, Unit)
Make_Extractor (gtk_aspect_frame_get, GtkAspectFrame_val, xalign, copy_double)
Make_Extractor (gtk_aspect_frame_get, GtkAspectFrame_val, yalign, copy_double)
Make_Extractor (gtk_aspect_frame_get, GtkAspectFrame_val, ratio, copy_double)
Make_Extractor (gtk_aspect_frame_get, GtkAspectFrame_val, obey_child, Val_bool)
*/
/* gtkhandlebox.h */
/*
#define GtkHandleBox_val(val) check_cast(GTK_HANDLE_BOX,val)
ML_0 (gtk_handle_box_new, Val_GtkWidget_sink)
ML_2 (gtk_handle_box_set_shadow_type, GtkHandleBox_val, Shadow_type_val, Unit)
ML_2 (gtk_handle_box_set_handle_position, GtkHandleBox_val,
      Position_type_val, Unit)
ML_2 (gtk_handle_box_set_snap_edge, GtkHandleBox_val,
      Position_type_val, Unit)
*/
/* gtkinvisible.h */
/* private class
ML_0 (gtk_invisible_new, Val_GtkWidget_sink)
*/

/* gtkviewport.h */
/*
#define GtkViewport_val(val) check_cast(GTK_VIEWPORT,val)
ML_2 (gtk_viewport_new, GtkAdjustment_val, GtkAdjustment_val,
      Val_GtkWidget_sink)
ML_1 (gtk_viewport_get_hadjustment, GtkViewport_val, Val_GtkWidget_sink)
ML_1 (gtk_viewport_get_vadjustment, GtkViewport_val, Val_GtkWidget)
ML_2 (gtk_viewport_set_hadjustment, GtkViewport_val, GtkAdjustment_val, Unit)
ML_2 (gtk_viewport_set_vadjustment, GtkViewport_val, GtkAdjustment_val, Unit)
ML_2 (gtk_viewport_set_shadow_type, GtkViewport_val, Shadow_type_val, Unit)
*/

/* gtkscrolledwindow.h */
#define GtkScrolledWindow_val(val) check_cast(GTK_SCROLLED_WINDOW,val)
/*
ML_2 (gtk_scrolled_window_new, GtkAdjustment_val ,GtkAdjustment_val,
      Val_GtkWidget_sink)
ML_2 (gtk_scrolled_window_set_hadjustment, GtkScrolledWindow_val ,
      GtkAdjustment_val, Unit)
ML_2 (gtk_scrolled_window_set_vadjustment, GtkScrolledWindow_val ,
      GtkAdjustment_val, Unit)
ML_1 (gtk_scrolled_window_get_hadjustment, GtkScrolledWindow_val,
      Val_GtkWidget)
ML_1 (gtk_scrolled_window_get_vadjustment, GtkScrolledWindow_val,
      Val_GtkWidget)
ML_3 (gtk_scrolled_window_set_policy, GtkScrolledWindow_val,
      Policy_type_val, Policy_type_val, Unit)
ML_2 (gtk_scrolled_window_set_shadow_type, GtkScrolledWindow_val,
      Shadow_type_val, Unit)
ML_1 (gtk_scrolled_window_get_shadow_type, GtkScrolledWindow_val,
      Val_shadow_type)
Make_Extractor (gtk_scrolled_window_get, GtkScrolledWindow_val,
		hscrollbar_policy, Val_policy_type)
Make_Extractor (gtk_scrolled_window_get, GtkScrolledWindow_val,
		vscrollbar_policy, Val_policy_type)
ML_2 (gtk_scrolled_window_set_placement, GtkScrolledWindow_val,
      Corner_type_val, Unit)
*/
ML_2 (gtk_scrolled_window_add_with_viewport, GtkScrolledWindow_val,
      GtkWidget_val, Unit)

/* gtksocket.h */
#ifdef _WIN32
Unsupported(gtk_socket_steal)
#else
#define GtkSocket_val(val) check_cast(GTK_SOCKET,val)
ML_2 (gtk_socket_steal, GtkSocket_val, XID_val, Unit)
#endif
