/* $Id: ml_gtk.c,v 1.127 2003/07/18 08:27:22 monate Exp $ */

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
#include "ml_pango.h"
#include "ml_gdk.h"
#include "ml_gtk.h"
#include "ml_gdkpixbuf.h"
#include "gobject_tags.h"
#include "gdk_tags.h"
#include "gtk_tags.h"

void ml_raise_gtk (const char *errmsg)
{
  static value * exn = NULL;
  if (exn == NULL)
      exn = caml_named_value ("gtkerror");
  raise_with_string (*exn, (char*)errmsg);
}

/* conversion functions */

#include "gtk_tags.c"

static Make_Flags_val (Dest_defaults_val)
static Make_Flags_val (Target_flags_val)
static Make_Flags_val (GdkModifier_val)

value Val_GtkWidget_func(gpointer w)
{
  return (Val_GtkWidget((GtkWidget*)w));
}

/* Init windows */

CAMLprim value ml_gtkwindow_init(value unit)
{
    /* Since these are declared const, must force gcc to call them! */
    GType t =
        gtk_message_dialog_get_type() +
        gtk_input_dialog_get_type() +
        gtk_color_selection_dialog_get_type() +
        gtk_file_selection_get_type() +
        gtk_font_selection_dialog_get_type() 
#ifndef _WIN32
        + gtk_plug_get_type()
#endif
;
    return Val_GType(t);
}

/* gtkobject.h */

#define gtk_object_ref_and_sink(w) (gtk_object_ref(w), gtk_object_sink(w))
Make_Val_final_pointer_ext(GtkObject, _sink , gtk_object_ref_and_sink,
                           gtk_object_unref, 20)
ML_1 (GTK_OBJECT_FLAGS, GtkObject_val, Val_int)
ML_1 (gtk_object_ref_and_sink, GtkObject_val, Unit)

/* gtkaccelgroup.h */

Make_OptFlags_val (Accel_flag_val)

#define Signal_name_val(val) String_val(Field(val,0))

#define Val_GtkAccelGroup_new(val) (Val_GObject_new(&val->parent))
ML_0 (gtk_accel_group_new, Val_GtkAccelGroup_new)
ML_1 (gtk_accel_group_lock, GtkAccelGroup_val, Unit)
ML_1 (gtk_accel_group_unlock, GtkAccelGroup_val, Unit)
ML_5 (gtk_accel_group_connect, GtkAccelGroup_val, Int_val,
      OptFlags_GdkModifier_val, OptFlags_Accel_flag_val,
      GClosure_val, Unit)
ML_3 (gtk_accel_group_disconnect_key, GtkAccelGroup_val, Int_val,
      OptFlags_GdkModifier_val, Val_bool)
ML_3 (gtk_accel_groups_activate, GObject_val, Int_val,
      OptFlags_GdkModifier_val, Val_bool)
ML_2 (gtk_accelerator_valid, Int_val, OptFlags_GdkModifier_val, Val_bool)
ML_1 (gtk_accelerator_set_default_mod_mask, OptFlags_GdkModifier_val, Unit)

ML_1(gtk_accel_map_load,String_val,Unit)
ML_1(gtk_accel_map_save,String_val,Unit)
ML_3(gtk_accel_map_add_entry,String_val,Int_val, OptFlags_GdkModifier_val, Unit)

/* gtkstyle.h */

#define Val_GtkStyle_new(val) (Val_GObject_new(&val->parent_instance))
ML_0 (gtk_style_new, Val_GtkStyle_new)
ML_1 (gtk_style_copy, GtkStyle_val, Val_GtkStyle_new)
ML_2 (gtk_style_attach, GtkStyle_val, GdkWindow_val, Val_GtkStyle)
ML_1 (gtk_style_detach, GtkStyle_val, Unit)
ML_3 (gtk_style_set_background, GtkStyle_val, GdkWindow_val, State_type_val,
      Unit)
ML_6 (gtk_draw_hline, GtkStyle_val, GdkWindow_val, State_type_val,
      Int_val, Int_val, Int_val, Unit)
ML_bc6 (ml_gtk_draw_hline)
ML_6 (gtk_draw_vline, GtkStyle_val, GdkWindow_val, State_type_val,
      Int_val, Int_val, Int_val, Unit)
ML_bc6 (ml_gtk_draw_vline)
Make_Array_Extractor (gtk_style_get, GtkStyle_val, State_type_val,
                      bg, Val_copy)
Make_Array_Setter (gtk_style_set, GtkStyle_val, State_type_val,
                   *GdkColor_val, bg)
Make_Array_Extractor (gtk_style_get, GtkStyle_val, State_type_val,
                      fg, Val_copy)
Make_Array_Setter (gtk_style_set, GtkStyle_val, State_type_val, *GdkColor_val,
                   fg)
Make_Array_Extractor (gtk_style_get, GtkStyle_val, State_type_val,
                      light, Val_copy)
Make_Array_Setter (gtk_style_set, GtkStyle_val, State_type_val,
                   *GdkColor_val, light)
Make_Array_Extractor (gtk_style_get, GtkStyle_val, State_type_val,
                      dark, Val_copy)
Make_Array_Setter (gtk_style_set, GtkStyle_val, State_type_val,
                   *GdkColor_val, dark)
Make_Array_Extractor (gtk_style_get, GtkStyle_val, State_type_val,
                      mid, Val_copy)
Make_Array_Setter (gtk_style_set, GtkStyle_val, State_type_val,
                   *GdkColor_val, mid)
Make_Array_Extractor (gtk_style_get, GtkStyle_val, State_type_val,
                      base, Val_copy)
Make_Array_Setter (gtk_style_set, GtkStyle_val, State_type_val,
                   *GdkColor_val, base)
Make_Array_Extractor (gtk_style_get, GtkStyle_val, State_type_val,
                      text, Val_copy)
Make_Array_Setter (gtk_style_set, GtkStyle_val, State_type_val,
                   *GdkColor_val, text)
Make_Extractor (gtk_style_get, GtkStyle_val, colormap, Val_GdkColormap)
Make_Extractor (gtk_style_get, GtkStyle_val, depth, Val_int)
ML_1 (gtk_style_get_font, GtkStyle_val, Val_GdkFont)
ML_2 (gtk_style_set_font, GtkStyle_val, GdkFont_val, Unit)
/*
CAMLprim value ml_gtk_style_set_font (value st, value font)
{
    GtkStyle *style = GtkStyle_val(st);
    if (style->font) gdk_font_unref(style->font);
    style->font = GdkFont_val(font);
    gdk_font_ref(style->font);
    return Val_unit;
}
*/

/* Doesn't seem useful
Make_Array_Extractor (gtk_style_get, GtkStyle_val, State_type_val,  dark_gc, Val_GdkGC)
Make_Array_Extractor (gtk_style_get, GtkStyle_val, State_type_val,  light_gc, Val_GdkGC)
*/

/* gtkobject.h */

ML_1 (gtk_object_destroy, GtkObject_val, Unit)
ML_1 (gtk_object_sink, GtkObject_val, Unit)

/* gtkdata.h */

/* gtkadjustment.h */

ML_6 (gtk_adjustment_new, Float_val, Float_val, Float_val, Float_val,
      Float_val, Float_val, Val_GtkObject_sink)
ML_bc6 (ml_gtk_adjustment_new)
ML_2 (gtk_adjustment_set_value, GtkAdjustment_val, Float_val, Unit)
ML_3 (gtk_adjustment_clamp_page, GtkAdjustment_val,
      Float_val, Float_val, Unit)
Make_Extractor (gtk_adjustment_get, GtkAdjustment_val, lower, copy_double)
Make_Extractor (gtk_adjustment_get, GtkAdjustment_val, upper, copy_double)
Make_Extractor (gtk_adjustment_get, GtkAdjustment_val, value, copy_double)
Make_Extractor (gtk_adjustment_get, GtkAdjustment_val, step_increment,
		copy_double)
Make_Extractor (gtk_adjustment_get, GtkAdjustment_val, page_increment,
		copy_double)
Make_Extractor (gtk_adjustment_get, GtkAdjustment_val, page_size, copy_double)
CAMLprim value ml_gtk_adjustment_set(value lower, value upper,
                            value step_increment, value page_increment,
                            value page_size, value adjustment)
{
    GtkAdjustment *adj = GtkAdjustment_val(adjustment);
#define Update_field(name) adj->name = Option_val(name,Double_val,adj->name)
    Update_field(lower);
    Update_field(upper);
    Update_field(step_increment);
    Update_field(page_increment);
    Update_field(page_size);
#undef Update_field
    return Val_unit;
}
ML_bc6(ml_gtk_adjustment_set)

/* gtktooltips.h */

#define GtkTooltips_val(val) check_cast(GTK_TOOLTIPS,val)
ML_0 (gtk_tooltips_new, Val_GtkAny)
ML_1 (gtk_tooltips_enable, GtkTooltips_val, Unit)
ML_1 (gtk_tooltips_disable, GtkTooltips_val, Unit)
ML_2 (gtk_tooltips_set_delay, GtkTooltips_val, Int_val, Unit)
ML_4 (gtk_tooltips_set_tip, GtkTooltips_val, GtkWidget_val,
      String_option_val, String_option_val, Unit)
/*
ML_3 (gtk_tooltips_set_colors, GtkTooltips_val,
      Option_val(arg2, GdkColor_val, NULL) Ignore,
      Option_val(arg3, GdkColor_val, NULL) Ignore,
      Unit)
*/

/* gtkwidget.h */

ML_1 (gtk_widget_unparent, GtkWidget_val, Unit)
ML_1 (gtk_widget_show, GtkWidget_val, Unit)
ML_1 (gtk_widget_show_now, GtkWidget_val, Unit)
ML_1 (gtk_widget_show_all, GtkWidget_val, Unit)
ML_1 (gtk_widget_hide, GtkWidget_val, Unit)
ML_1 (gtk_widget_hide_all, GtkWidget_val, Unit)
ML_1 (gtk_widget_map, GtkWidget_val, Unit)
ML_1 (gtk_widget_unmap, GtkWidget_val, Unit)
ML_1 (gtk_widget_realize, GtkWidget_val, Unit)
ML_1 (gtk_widget_unrealize, GtkWidget_val, Unit)
ML_1 (gtk_widget_queue_draw, GtkWidget_val, Unit)
ML_1 (gtk_widget_queue_resize, GtkWidget_val, Unit)
ML_2 (gtk_widget_draw, GtkWidget_val,
      Option_val(arg2,GdkRectangle_val,NULL) Ignore, Unit)
/*
ML_1 (gtk_widget_draw_focus, GtkWidget_val, Unit)
ML_1 (gtk_widget_draw_default, GtkWidget_val, Unit)
ML_1 (gtk_widget_draw_children, GtkWidget_val, Unit)
*/
ML_2 (gtk_widget_event, GtkWidget_val, GdkEvent_val, Val_bool)
ML_1 (gtk_widget_activate, GtkWidget_val, Val_bool)
ML_2 (gtk_widget_reparent, GtkWidget_val, GtkWidget_val, Unit)
/* ML_3 (gtk_widget_popup, GtkWidget_val, Int_val, Int_val, Unit) */
CAMLprim value ml_gtk_widget_intersect (value w, value area)
{
    GdkRectangle inter;
    if (gtk_widget_intersect(GtkWidget_val(w), GdkRectangle_val(area), &inter))
	return ml_some (Val_copy (inter));
    return Val_unit;
}
/* properties
ML_1 (gtk_widget_grab_focus, GtkWidget_val, Unit)
ML_1 (gtk_widget_grab_default, GtkWidget_val, Unit)
ML_2 (gtk_widget_set_name, GtkWidget_val, String_val, Unit)
ML_1 (gtk_widget_get_name, GtkWidget_val, Val_string)
ML_2 (gtk_widget_set_sensitive, GtkWidget_val, Bool_val, Unit)
ML_2 (gtk_widget_set_events, GtkWidget_val, Flags_Event_mask_val, Unit)
ML_2 (gtk_widget_set_extension_events, GtkWidget_val, Extension_mode_val,
      Unit)
ML_2 (gtk_widget_set_style, GtkWidget_val, GtkStyle_val, Unit)
ML_1 (gtk_widget_get_style, GtkWidget_val, Val_GtkStyle)
ML_3 (gtk_widget_set_usize, GtkWidget_val, Int_val, Int_val, Unit)
ML_3 (gtk_widget_set_size_request, GtkWidget_val, Int_val, Int_val, Unit)
*/
ML_2 (gtk_widget_set_state, GtkWidget_val, State_type_val, Unit)
ML_3 (gtk_widget_set_uposition, GtkWidget_val, Int_val, Int_val, Unit)
ML_2 (gtk_widget_add_events, GtkWidget_val, Flags_Event_mask_val, Unit)
ML_1 (gtk_widget_get_toplevel, GtkWidget_val, Val_GtkWidget)
ML_2 (gtk_widget_get_ancestor, GtkWidget_val, Int_val, Val_GtkWidget)
ML_1 (gtk_widget_get_colormap, GtkWidget_val, Val_GdkColormap)
ML_1 (gtk_widget_get_visual, GtkWidget_val, (value))
CAMLprim value ml_gtk_widget_get_pointer (value w)
{
    int x,y;
    value ret;
    gtk_widget_get_pointer (GtkWidget_val(w), &x, &y);
    ret = alloc_small (2,0);
    Field(ret,0) = Val_int(x);
    Field(ret,1) = Val_int(y);
    return ret;
}
ML_2 (gtk_widget_is_ancestor, GtkWidget_val, GtkWidget_val, Val_bool)

ML_1 (gtk_widget_ensure_style, GtkWidget_val, Unit)
ML_3 (gtk_widget_modify_fg, GtkWidget_val, State_type_val, GdkColor_val, Unit)
ML_3 (gtk_widget_modify_bg, GtkWidget_val, State_type_val, GdkColor_val, Unit)
ML_3 (gtk_widget_modify_text, GtkWidget_val, State_type_val, GdkColor_val,Unit)
ML_3 (gtk_widget_modify_base, GtkWidget_val, State_type_val, GdkColor_val,Unit)
ML_2 (gtk_widget_modify_font, GtkWidget_val, PangoFontDescription_val, Unit)
ML_1 (gtk_widget_get_pango_context, GtkWidget_val, Val_PangoContext)
ML_1 (gtk_widget_create_pango_context, GtkWidget_val, Val_PangoContext_new)
ML_6 (gtk_widget_add_accelerator, GtkWidget_val, Signal_name_val,
      GtkAccelGroup_val, Char_val, OptFlags_GdkModifier_val,
      OptFlags_Accel_flag_val, Unit)
ML_bc6 (ml_gtk_widget_add_accelerator)
ML_4 (gtk_widget_remove_accelerator, GtkWidget_val, GtkAccelGroup_val,
      Char_val, OptFlags_GdkModifier_val, Unit)

ML_3 (gtk_widget_set_accel_path, 
      GtkWidget_val, String_val, GtkAccelGroup_val, Unit)
/*
ML_1 (gtk_widget_lock_accelerators, GtkWidget_val, Unit)
ML_1 (gtk_widget_unlock_accelerators, GtkWidget_val, Unit)
ML_1 (gtk_widget_accelerators_locked, GtkWidget_val, Val_bool)
*/

Make_Extractor (GtkWidget, GtkWidget_val, window, Val_GdkWindow)
Make_Extractor (gtk_widget, GtkWidget_val, parent, Val_GtkWidget)
static value Val_GtkAllocation (GtkAllocation allocation)
{
    value ret = alloc_small (4, 0);
    Field(ret,0) = Val_int(allocation.x);
    Field(ret,1) = Val_int(allocation.y);
    Field(ret,2) = Val_int(allocation.width);
    Field(ret,3) = Val_int(allocation.height);
    return ret;
}
Make_Extractor (gtk_widget, GtkWidget_val, allocation, Val_GtkAllocation)
ML_1(Val_GtkAllocation, *(GtkAllocation*)Pointer_val, (value))
/*
#define GtkAllocation_val(val) ((GtkAllocation*)Pointer_val(val))
Make_Extractor (gtk_allocation, GtkAllocation_val, x, Val_int)
Make_Extractor (gtk_allocation, GtkAllocation_val, y, Val_int)
Make_Extractor (gtk_allocation, GtkAllocation_val, width, Val_int)
Make_Extractor (gtk_allocation, GtkAllocation_val, height, Val_int)
*/

ML_2 (gtk_widget_set_app_paintable, GtkWidget_val, Bool_val, Unit)

ML_2 (gtk_widget_set_visual, GtkWidget_val, GdkVisual_val, Unit)
ML_2 (gtk_widget_set_colormap, GtkWidget_val, GdkColormap_val, Unit)
ML_1 (gtk_widget_set_default_visual, GdkVisual_val, Unit)
ML_1 (gtk_widget_set_default_colormap, GdkColormap_val, Unit)
ML_0 (gtk_widget_get_default_visual, Val_GdkVisual)
ML_0 (gtk_widget_get_default_colormap, Val_GdkColormap)
ML_1 (gtk_widget_push_visual, GdkVisual_val, Unit)
ML_1 (gtk_widget_push_colormap, GdkColormap_val, Unit)
ML_0 (gtk_widget_pop_visual, Unit)
ML_0 (gtk_widget_pop_colormap, Unit)

ML_4 (gtk_widget_render_icon, GtkWidget_val, String_val, Icon_size_val, String_option_val, Val_GdkPixbuf)

/* gtkdnd.h */

CAMLprim value ml_gtk_drag_dest_set (value w, value f, value t, value a)
{
  GtkTargetEntry *targets = (GtkTargetEntry *)Val_unit;
  int n_targets, i;
  
  CAMLparam4 (w,f,t,a);
  n_targets = Wosize_val(t);
  if (n_targets)
      targets = (GtkTargetEntry *)
	  alloc (Wosize_asize(n_targets * sizeof(GtkTargetEntry)),
		 Abstract_tag);
  for (i=0; i<n_targets; i++) {
    targets[i].target = String_val(Field(Field(t, i), 0));
    targets[i].flags = Flags_Target_flags_val(Field(Field(t, i), 1));
    targets[i].info = Int_val(Field(Field(t, i), 2));
  }
  gtk_drag_dest_set (GtkWidget_val(w), Flags_Dest_defaults_val(f),
		     targets, n_targets, Flags_GdkDragAction_val(a));
  CAMLreturn(Val_unit);
}
ML_1 (gtk_drag_dest_unset, GtkWidget_val, Unit)
ML_4 (gtk_drag_finish, GdkDragContext_val, Bool_val, Bool_val, Int32_val, Unit)
ML_4 (gtk_drag_get_data, GtkWidget_val, GdkDragContext_val,
      GdkAtom_val, Int32_val, Unit)
ML_1 (gtk_drag_get_source_widget, GdkDragContext_val, Val_GtkWidget)
ML_1 (gtk_drag_highlight, GtkWidget_val, Unit)
ML_1 (gtk_drag_unhighlight, GtkWidget_val, Unit)
ML_4 (gtk_drag_set_icon_widget, GdkDragContext_val, GtkWidget_val,
      Int_val, Int_val, Unit)
ML_6 (gtk_drag_set_icon_pixmap, GdkDragContext_val, GdkColormap_val,
      GdkPixmap_val, Option_val(arg4, GdkBitmap_val, NULL) Ignore,
      Int_val, Int_val, Unit)
ML_bc6 (ml_gtk_drag_set_icon_pixmap)
ML_1 (gtk_drag_set_icon_default, GdkDragContext_val, Unit)
ML_5 (gtk_drag_set_default_icon, GdkColormap_val,
      GdkPixmap_val, Option_val(arg3, GdkBitmap_val, NULL) Ignore,
      Int_val, Int_val, Unit)
CAMLprim value ml_gtk_drag_source_set (value w, value m, value t, value a)
{
  GtkTargetEntry *targets = (GtkTargetEntry *)Val_unit;
  int n_targets, i;
  CAMLparam4 (w,m,t,a);
  
  n_targets = Wosize_val(t);
  if (n_targets)
      targets = (GtkTargetEntry *)
	  alloc (Wosize_asize(n_targets * sizeof(GtkTargetEntry)),
		 Abstract_tag);
  for (i=0; i<n_targets; i++) {
    targets[i].target = String_val(Field(Field(t, i), 0));
    targets[i].flags = Flags_Target_flags_val(Field(Field(t, i), 1));
    targets[i].info = Int_val(Field(Field(t, i), 2));
  }
  gtk_drag_source_set (GtkWidget_val(w), OptFlags_GdkModifier_val(m),
		       targets, n_targets, Flags_GdkDragAction_val(a));
  CAMLreturn(Val_unit);
}
ML_4 (gtk_drag_source_set_icon, GtkWidget_val, GdkColormap_val,
      GdkPixmap_val, Option_val(arg4, GdkBitmap_val, NULL) Ignore, Unit)
ML_1 (gtk_drag_source_unset, GtkWidget_val, Unit)

/* gtkwidget.h / gtkselection.h */

Make_Val_final_pointer(GtkSelectionData, Ignore, gtk_selection_data_free, 20)
#define GtkSelectionData_val(val) ((GtkSelectionData *)Pointer_val(val))

Make_Extractor (gtk_selection_data, GtkSelectionData_val, selection,
                Val_GdkAtom)
Make_Extractor (gtk_selection_data, GtkSelectionData_val, target, Val_GdkAtom)
Make_Extractor (gtk_selection_data, GtkSelectionData_val, type, Val_GdkAtom)
Make_Extractor (gtk_selection_data, GtkSelectionData_val, format, Val_int)
CAMLprim value ml_gtk_selection_data_get_data (value val)
{
    value ret;
    GtkSelectionData *data = GtkSelectionData_val(val);

    if (data->length < 0) ml_raise_null_pointer();
    ret = alloc_string (data->length);
    if (data->length) memcpy ((void*)ret, data->data, data->length);
    return ret;
}
ML_1 (gtk_selection_data_copy, GtkSelectionData_val, Val_GtkSelectionData)

ML_4 (gtk_selection_data_set, GtkSelectionData_val, GdkAtom_val, Int_val,
      Insert((guchar*)String_option_val(arg4))
      Option_val(arg4, string_length, -1) Ignore,
      Unit)

ML_3 (gtk_selection_owner_set, GtkWidget_val, GdkAtom_val,
      Int32_val, Val_bool)
ML_4 (gtk_selection_add_target, GtkWidget_val, GdkAtom_val,
      GdkAtom_val, Int_val, Unit)
ML_4 (gtk_selection_convert, GtkWidget_val, GdkAtom_val,
      GdkAtom_val, Int32_val, Val_bool)

/* gtkclipboard.h */

ML_1 (gtk_clipboard_get, GdkAtom_val, Val_pointer)
ML_1 (gtk_clipboard_clear, GtkClipboard_val, Unit)
ML_2 (gtk_clipboard_set_text, GtkClipboard_val, SizedString_val, Unit)
ML_2 (gtk_clipboard_wait_for_contents, GtkClipboard_val, GdkAtom_val,
      Val_GtkSelectionData)
CAMLprim value ml_gtk_clipboard_wait_for_text (value c)
{
  const char *res = gtk_clipboard_wait_for_text (GtkClipboard_val(c));
  return (res != NULL ? ml_some(copy_string_g_free((char*)res)) : Val_unit);
}
static void clipboard_received_func (GtkClipboard *clipboard,
                                     GtkSelectionData *selection_data,
                                     gpointer data)
{
  value arg = Val_pointer (selection_data);
  callback (*(value*)data, arg);
  ml_global_root_destroy (data);
}
CAMLprim value ml_gtk_clipboard_request_contents (value c, value a, value f)
{
  void *f_p = ml_global_root_new (f);
  gtk_clipboard_request_contents (GtkClipboard_val(c), GdkAtom_val(a),
                                  clipboard_received_func, f_p);
  return Val_unit;
}
static void clipboard_text_received_func (GtkClipboard *clipboard,
                                          const gchar *text,
                                          gpointer data)
{
  value arg = (text != NULL ? ml_some(copy_string(text)) : Val_unit);
  callback (*(value*)data, arg);
  ml_global_root_destroy (data);
}
CAMLprim value ml_gtk_clipboard_request_text (value c, value f)
{
  void *f_p = ml_global_root_new (f);
  gtk_clipboard_request_text (GtkClipboard_val(c),
                              clipboard_text_received_func, f_p);
  return Val_unit;
}
/*
static void clipboard_get_func (GtkClipboard *clipboard,
                                GtkSelectionData *selection_data,
                                guint info, gpointer data)
{
  value arg = Val_pointer (selection_data);
  callback2 (Field(*(value*)data,0), arg, Val_int(info));
}
static void clipboard_clear_func (GtkClipboard *clipboard, gpointer data)
{
  callback (Field(*(value*)data,1), Val_unit);
  ml_global_root_destroy (data);
}
*/

/* gtkcontainer.h */

#define GtkContainer_val(val) check_cast(GTK_CONTAINER,val)
/* properties
ML_2 (gtk_container_set_border_width, GtkContainer_val, Int_val, Unit)
ML_1 (gtk_container_get_border_width, GtkContainer_val, Val_int)
ML_2 (gtk_container_set_resize_mode, GtkContainer_val, Resize_mode_val, Unit)
ML_1 (gtk_container_get_resize_mode, GtkContainer_val, Val_resize_mode)
*/
ML_2 (gtk_container_add, GtkContainer_val, GtkWidget_val, Unit)
ML_2 (gtk_container_remove, GtkContainer_val, GtkWidget_val, Unit)
ML_1 (gtk_container_check_resize, GtkContainer_val, Unit)
static void ml_gtk_simple_callback (GtkWidget *w, gpointer data)
{
    value val, *clos = (value*)data;
    val = Val_GtkWidget(w);
    callback (*clos, val);
}
CAMLprim value ml_gtk_container_foreach (value w, value clos)
{
    CAMLparam1(clos);
    gtk_container_foreach (GtkContainer_val(w), ml_gtk_simple_callback,
			   &clos);
    CAMLreturn(Val_unit);
}
ML_2 (gtk_container_set_focus_child, GtkContainer_val, GtkWidget_val, Unit)
ML_2 (gtk_container_set_focus_vadjustment, GtkContainer_val,
      GtkAdjustment_val, Unit)
ML_2 (gtk_container_set_focus_hadjustment, GtkContainer_val,
      GtkAdjustment_val, Unit)

/* gtkitem.h */

ML_1 (gtk_item_select, GtkItem_val, Unit)
ML_1 (gtk_item_deselect, GtkItem_val, Unit)
ML_1 (gtk_item_toggle, GtkItem_val, Unit)

/* gtkdialog.h */

static void window_unref (GtkObject *w)
{
    /* If the window exists, has no parent, is still not visible,
       and has only two references (mine and toplevel_list),
       then destroy it. */
    if (GTK_WINDOW(w)->has_user_ref_count && !GTK_WIDGET_VISIBLE(w)
        && G_OBJECT(w)->ref_count == 2)
        gtk_object_destroy (w);
    gtk_object_unref(w);
}
Make_Val_final_pointer_ext (GtkObject, _window, gtk_object_ref, window_unref,
                            20)
#define Val_GtkWidget_window(w) Val_GtkObject_window(GTK_OBJECT(w))

#define GtkDialog_val(val) check_cast(GTK_DIALOG,val)
/* ML_0 (gtk_dialog_new, Val_GtkWidget_window) */
Make_Extractor (GtkDialog, GtkDialog_val, action_area, Val_GtkWidget)
Make_Extractor (GtkDialog, GtkDialog_val, vbox, Val_GtkWidget)
ML_2 (gtk_dialog_response, GtkDialog_val, Int_val, Unit)
ML_3 (gtk_dialog_add_button, GtkDialog_val, String_val, Int_val, Unit)
ML_3 (gtk_dialog_set_response_sensitive, GtkDialog_val, Int_val, Bool_val, Unit)
ML_2 (gtk_dialog_set_default_response, GtkDialog_val, Int_val, Unit)
ML_1 (gtk_dialog_run, GtkDialog_val, Val_int)
     /* gtk_dialog_add_action_widget */

/* gtkinputdialog.h */

/* ML_0 (gtk_input_dialog_new, Val_GtkWidget_window) */

/* gtkfileselection.h */

#define GtkFileSelection_val(val) check_cast(GTK_FILE_SELECTION,val)
ML_1 (gtk_file_selection_new, String_val, Val_GtkWidget_window)
ML_2 (gtk_file_selection_complete, GtkFileSelection_val, String_val, Unit)
/* properties
ML_2 (gtk_file_selection_set_filename, GtkFileSelection_val, String_val, Unit)
ML_1 (gtk_file_selection_get_filename, GtkFileSelection_val, Val_string)
ML_1 (gtk_file_selection_show_fileop_buttons, GtkFileSelection_val, Unit)
ML_1 (gtk_file_selection_hide_fileop_buttons, GtkFileSelection_val, Unit)
ML_2 (gtk_file_selection_set_select_multiple, GtkFileSelection_val, Bool_val,
      Unit)
ML_1 (gtk_file_selection_get_select_multiple, GtkFileSelection_val, Val_bool)
*/
CAMLprim value ml_gtk_file_selection_get_selections (value sel)
{
  gchar** selections =
    gtk_file_selection_get_selections(GtkFileSelection_val(sel));
  gchar** orig = selections;
  CAMLparam0();
  CAMLlocal3(ret,prev,next);
  for (prev = (value)((&ret)-1); *selections != NULL; selections++) {
    next = alloc(2,0);
    Store_field(prev, 1, next);
    Store_field(next, 0, Val_string(*selections));
    prev = next;
  }
  Field(prev,1) = Val_unit;
  g_strfreev(orig);
  CAMLreturn(ret);
}
    
Make_Extractor (gtk_file_selection_get, GtkFileSelection_val, ok_button,
		Val_GtkWidget)
Make_Extractor (gtk_file_selection_get, GtkFileSelection_val, cancel_button,
		Val_GtkWidget)
Make_Extractor (gtk_file_selection_get, GtkFileSelection_val, help_button,
		Val_GtkWidget)
Make_Extractor (gtk_file_selection_get, GtkFileSelection_val, file_list,
		Val_GtkWidget)

/* gtkwindow.h */

#define GtkWindow_val(val) check_cast(GTK_WINDOW,val)
ML_1 (gtk_window_new, Window_type_val, Val_GtkWidget_window)
/* ML_2 (gtk_window_set_title, GtkWindow_val, String_val, Unit) */
ML_3 (gtk_window_set_wmclass, GtkWindow_val, String_val, String_val, Unit)
Make_Extractor (gtk_window_get, GtkWindow_val, wmclass_name, Val_optstring)
Make_Extractor (gtk_window_get, GtkWindow_val, wmclass_class, Val_optstring)
ML_2 (gtk_window_add_accel_group, GtkWindow_val,
      GtkAccelGroup_val, Unit)
ML_2 (gtk_window_remove_accel_group, GtkWindow_val,
      GtkAccelGroup_val, Unit)
ML_1 (gtk_window_activate_focus, GtkWindow_val, Val_bool)
ML_1 (gtk_window_activate_default, GtkWindow_val, Val_bool)
CAMLprim value ml_gtk_window_set_geometry_hints (
  value win, value pos, value min_size, value max_size, value base_size, 
  value aspect, value resize_inc, value win_gravity, value user_pos,
  value user_size, value wid )
{
  GdkWindowHints hints = 0;
  GdkGeometry geom;
  
  if (pos != Val_unit && Field(pos,0) != Val_unit) hints |= GDK_HINT_POS;
  if (min_size != Val_unit) {
    hints |= GDK_HINT_MIN_SIZE;
    geom.min_width = Int_val (Field(Field(min_size,0),0));
    geom.min_height = Int_val (Field(Field(min_size,0),1));
  }
  if (max_size != Val_unit) {
    hints |= GDK_HINT_MAX_SIZE;
    geom.max_width = Int_val (Field(Field(max_size,0),0));
    geom.max_height = Int_val (Field(Field(max_size,0),1));
  }
  if (base_size != Val_unit) {
    hints |= GDK_HINT_BASE_SIZE;
    geom.base_width = Int_val (Field(Field(base_size,0),0));
    geom.base_height = Int_val (Field(Field(base_size,0),1));
  }
  if (aspect != Val_unit) {
    hints |= GDK_HINT_ASPECT;
    geom.min_aspect = Double_val (Field(Field(aspect,0),0));
    geom.max_aspect = Double_val (Field(Field(aspect,0),1));
  }
  if (resize_inc != Val_unit) {
    hints |= GDK_HINT_RESIZE_INC;
    geom.width_inc = Int_val (Field(Field(resize_inc,0),0));
    geom.height_inc = Int_val (Field(Field(resize_inc,0),1));
  }
  if (win_gravity != Val_unit) {
    hints |= GDK_HINT_WIN_GRAVITY;
    geom.win_gravity = Gravity_val (Field(win_gravity,0));
  }
  if (user_pos != Val_unit && Field(user_pos,0) != Val_unit)
    hints |= GDK_HINT_USER_POS;
  if (user_size != Val_unit && Field(user_size,0) != Val_unit)
    hints |= GDK_HINT_USER_SIZE;

  gtk_window_set_geometry_hints (GtkWindow_val(win), GtkWidget_val(wid),
                                 &geom, hints);
  return Val_unit;
}
ML_bc11 (ml_gtk_window_set_geometry_hints)
ML_2 (gtk_window_set_gravity, GtkWindow_val, Gravity_val, Unit)
ML_1 (gtk_window_get_gravity, GtkWindow_val, Val_gravity)
ML_2 (gtk_window_set_transient_for, GtkWindow_val, GtkWindow_val, Unit)
ML_1 (gtk_window_get_transient_for, GtkWindow_val, Val_GtkWidget)
static value wrap_widget (gpointer arg)
{ return Val_GtkWidget(arg); }
CAMLprim value ml_gtk_window_list_toplevels(value unit)
{  return Val_GList(gtk_window_list_toplevels(), wrap_widget); }
ML_3 (gtk_window_add_mnemonic, GtkWindow_val, Int_val, GtkWidget_val, Unit)
ML_3 (gtk_window_remove_mnemonic, GtkWindow_val, Int_val, GtkWidget_val, Unit)
ML_3 (gtk_window_mnemonic_activate, GtkWindow_val, Int_val(arg3) Ignore,
      OptFlags_GdkModifier_val(arg2) Ignore, Unit)
ML_1 (gtk_window_get_focus, GtkWindow_val, Val_GtkWidget)
ML_2 (gtk_window_set_focus, GtkWindow_val, GtkWidget_val, Unit)
ML_2 (gtk_window_set_default, GtkWindow_val, GtkWidget_val, Unit)
ML_1 (gtk_window_present, GtkWindow_val, Unit)
ML_1 (gtk_window_iconify, GtkWindow_val, Unit)
ML_1 (gtk_window_deiconify, GtkWindow_val, Unit)
ML_1 (gtk_window_stick, GtkWindow_val, Unit)
ML_1 (gtk_window_unstick, GtkWindow_val, Unit)
ML_1 (gtk_window_maximize, GtkWindow_val, Unit)
ML_1 (gtk_window_unmaximize, GtkWindow_val, Unit)
#ifdef HASGTK22
ML_1 (gtk_window_fullscreen, GtkWindow_val, Unit)
ML_1 (gtk_window_unfullscreen, GtkWindow_val, Unit)
#else
Unsupported (gtk_window_fullscreen)
Unsupported (gtk_window_unfullscreen)
#endif
ML_2 (gtk_window_set_decorated, GtkWindow_val, Bool_val, Unit)
ML_2 (gtk_window_set_mnemonic_modifier, GtkWindow_val,
      Flags_GdkModifier_val, Unit)
ML_3 (gtk_window_move, GtkWindow_val, Int_val, Int_val, Unit)
ML_2 (gtk_window_parse_geometry, GtkWindow_val, String_val, Val_bool)
ML_1 (gtk_window_reshow_with_initial_size, GtkWindow_val, Unit)
ML_3 (gtk_window_resize, GtkWindow_val, Int_val, Int_val, Unit)
ML_2 (gtk_window_set_role, GtkWindow_val, String_val, Unit)
ML_1 (gtk_window_get_role, GtkWindow_val, Val_optstring)

/* gtkmessagedialog.h */
ML_4 (gtk_message_dialog_new, Option_val(arg1,GtkWindow_val,NULL) Ignore,
      Insert(0) Message_type_val, Buttons_type_val,
      Insert(String_val(arg4)[0] != 0 ? "%s" : NULL) String_val,
      Val_GtkWidget_window)

/* gtkcolorsel.h */

/* useless
#define GtkColorSelection_val(val) check_cast(GTK_COLOR_SELECTION,val)
ML_0 (gtk_color_selection_new, Val_GtkWidget_sink)
ML_2 (gtk_color_selection_set_update_policy, GtkColorSelection_val,
      Update_type_val, Unit)
ML_2 (gtk_color_selection_set_opacity, GtkColorSelection_val,
      Bool_val, Unit)
CAMLprim value ml_gtk_color_selection_set_color
         (value w, value red, value green, value blue, value opacity)
{
    double color[4];
    color[0] = Double_val(red);
    color[1] = Double_val(green);
    color[2] = Double_val(blue);
    color[3] = Option_val(opacity,Double_val,0.0);
    gtk_color_selection_set_color (GtkColorSelection_val(w), color);
    return Val_unit;
}
CAMLprim value ml_gtk_color_selection_get_color (value w)
{
    value ret;
    double color[4];
    color[3] = 0.0;
    gtk_color_selection_get_color (GtkColorSelection_val(w), color);
    ret = alloc (4*Double_wosize, Double_array_tag);
    Store_double_field (ret, 0, color[0]);
    Store_double_field (ret, 1, color[1]);
    Store_double_field (ret, 2, color[2]);
    Store_double_field (ret, 3, color[3]);
    return ret;
}
ML_1 (gtk_color_selection_dialog_new, String_val, Val_GtkWidget_window)
*/
#define GtkColorSelectionDialog_val(val) check_cast(GTK_COLOR_SELECTION_DIALOG,val)
Make_Extractor (gtk_color_selection_dialog, GtkColorSelectionDialog_val, ok_button, Val_GtkWidget)
Make_Extractor (gtk_color_selection_dialog, GtkColorSelectionDialog_val, cancel_button, Val_GtkWidget)
Make_Extractor (gtk_color_selection_dialog, GtkColorSelectionDialog_val, help_button, Val_GtkWidget)
Make_Extractor (gtk_color_selection_dialog, GtkColorSelectionDialog_val, colorsel, Val_GtkWidget)

/* gtkfontsel.h */

/*
#define GtkFontSelection_val(val) \
   check_cast(GTK_FONT_SELECTION,val)
ML_0 (gtk_font_selection_new, Val_GtkWidget_sink)
ML_1 (gtk_font_selection_get_font, GtkFontSelection_val,
      Val_GdkFont)
ML_1 (gtk_font_selection_get_font_name, GtkFontSelection_val,
      copy_string_check)
ML_2 (gtk_font_selection_set_font_name, GtkFontSelection_val,
      String_val, Val_bool)
ML_9 (gtk_font_selection_set_filter, GtkFontSelection_val,
      Font_filter_type_val, Flags_Font_type_val,
      (gchar**), (gchar**), (gchar**),
      (gchar**), (gchar**), (gchar**), Unit)
ML_bc9 (ml_gtk_font_selection_set_filter)
ML_1 (gtk_font_selection_get_preview_text, GtkFontSelection_val,
      copy_string)
ML_2 (gtk_font_selection_set_preview_text, GtkFontSelection_val,
      String_val, Unit)
*/

#define GtkFontSelectionDialog_val(val) \
   check_cast(GTK_FONT_SELECTION_DIALOG,val)
/*
ML_1 (gtk_font_selection_dialog_new, String_option_val, Val_GtkWidget_window)
ML_1 (gtk_font_selection_dialog_get_font, GtkFontSelectionDialog_val,
      Val_GdkFont)
ML_1 (gtk_font_selection_dialog_get_font_name, GtkFontSelectionDialog_val,
      copy_string_check)
ML_2 (gtk_font_selection_dialog_set_font_name, GtkFontSelectionDialog_val,
      String_val, Val_bool)
ML_9 (gtk_font_selection_dialog_set_filter, GtkFontSelectionDialog_val,
      Font_filter_type_val, Flags_Font_type_val,
      (gchar**), (gchar**), (gchar**),
      (gchar**), (gchar**), (gchar**), Unit)
ML_bc9 (ml_gtk_font_selection_dialog_set_filter)
ML_1 (gtk_font_selection_dialog_get_preview_text, GtkFontSelectionDialog_val,
      copy_string)
ML_2 (gtk_font_selection_dialog_set_preview_text, GtkFontSelectionDialog_val,
      String_val, Unit)
*/
Make_Extractor (gtk_font_selection_dialog, GtkFontSelectionDialog_val,
                fontsel, Val_GtkWidget)
Make_Extractor (gtk_font_selection_dialog, GtkFontSelectionDialog_val,
		ok_button, Val_GtkWidget)
Make_Extractor (gtk_font_selection_dialog, GtkFontSelectionDialog_val,
		apply_button, Val_GtkWidget)
Make_Extractor (gtk_font_selection_dialog, GtkFontSelectionDialog_val,
		cancel_button, Val_GtkWidget)

/* gtkplug.h */
#ifdef _WIN32
Unsupported(gtk_plug_new)
#else
ML_1 (gtk_plug_new, XID_val, Val_GtkWidget_window)
#endif

/* gtkmain.h */

CAMLprim value ml_gtk_init (value argv)
{
    CAMLparam1 (argv);
    int argc = Wosize_val(argv), i;
    CAMLlocal1 (copy);

    copy = (argc ? alloc (argc, Abstract_tag) : Atom(0));
    for (i = 0; i < argc; i++) Field(copy,i) = Field(argv,i);
    if( !gtk_init_check (&argc, (char ***)&copy) ){
      ml_raise_gtk ("ml_gtk_init: initialization failed");
    }

    argv = (argc ? alloc (argc, 0) : Atom(0));
    for (i = 0; i < argc; i++) modify(&Field(argv,i), Field(copy,i));
    CAMLreturn (argv);
}
ML_1 (gtk_exit, Int_val, Unit)
ML_0 (gtk_set_locale, Val_string)
ML_0 (gtk_disable_setlocale, Unit)
ML_0 (gtk_main, Unit)
ML_1 (gtk_main_iteration_do, Bool_val, Val_bool)
ML_0 (gtk_main_quit, Unit)
ML_1 (gtk_grab_add, GtkWidget_val, Unit)
ML_1 (gtk_grab_remove, GtkWidget_val, Unit)
ML_0 (gtk_grab_get_current, Val_GtkWidget)
CAMLprim value ml_gtk_get_version (value unit)
{
    value ret = alloc_small(3,0);
    Field(ret,0) = Val_int(gtk_major_version);
    Field(ret,1) = Val_int(gtk_minor_version);
    Field(ret,2) = Val_int(gtk_micro_version);
    return ret;
}

ML_0 (gtk_get_current_event_time,copy_int32)

/* Marshalling */

/*
void ml_gtk_callback_marshal (GtkObject *object, gpointer data,
			       guint nargs, GtkArg *args)
{
    value vargs = alloc_small(3,0);

    CAMLparam1 (vargs);
    Field(vargs,0) = (value) object;
    Field(vargs,1) = Val_int(nargs);
    Field(vargs,2) = (value) args;

    callback (*(value*)data, vargs);

    Field(vargs,0) = Val_int(-1);
    Field(vargs,1) = Val_int(-1);
    CAMLreturn0;
}

CAMLprim value ml_gtk_arg_shift (GtkArg *args, value index)
{
    return (value) (&args[Int_val(index)]);
}

CAMLprim value ml_gtk_arg_get_type (GtkArg *arg)
{
    return Val_int (arg->type);
}

CAMLprim value ml_gtk_arg_get (GtkArg *arg)
{
    CAMLparam0();
    CAMLlocal1(tmp);
    value ret = Val_unit;
    GtkFundamentalType type = GTK_FUNDAMENTAL_TYPE(arg->type);
    int tag;

    switch (type) {
    case GTK_TYPE_CHAR:
        tag = 0;
        tmp = Int_val(GTK_VALUE_CHAR(*arg));
        break;
    case GTK_TYPE_BOOL:
        tag = 1;
        tmp = Val_bool(GTK_VALUE_BOOL(*arg));
        break;
    case GTK_TYPE_INT:
    case GTK_TYPE_ENUM:
    case GTK_TYPE_UINT:
    case GTK_TYPE_FLAGS:
        tag = 2;
        tmp = Val_int (GTK_VALUE_INT(*arg)); break;
    case GTK_TYPE_LONG:
    case GTK_TYPE_ULONG:
        tag = 2;
        tmp = Val_int (GTK_VALUE_LONG(*arg)); break;
    case GTK_TYPE_FLOAT:
        tag = 3;
        tmp = copy_double ((double)GTK_VALUE_FLOAT(*arg)); break;
    case GTK_TYPE_DOUBLE:
        tag = 3;
        tmp = copy_double (GTK_VALUE_DOUBLE(*arg)); break;
    case GTK_TYPE_STRING:
        tag = 4;
        tmp = Val_option (GTK_VALUE_STRING(*arg), copy_string); break;
    case GTK_TYPE_OBJECT:
        tag = 5;
        tmp = Val_option (GTK_VALUE_OBJECT(*arg), Val_GtkObject); break;
    case GTK_TYPE_BOXED:
    case GTK_TYPE_POINTER:
        tag = 6;
        tmp = Val_option (GTK_VALUE_POINTER(*arg), Val_pointer); break;
    default:
        tag = -1;
    }
    if (tag != -1) {
        ret = alloc_small(1,tag);
        Field(ret,0) = tmp;
    }
    CAMLreturn(ret);
}

CAMLprim value ml_gtk_arg_set_retloc (GtkArg *arg, value val)
{
    value type = Fundamental_type_val(Is_block(val) ? Field(val,0) : val);
    value data = (Is_block(val) ? Field(val,1) : 0);
    if (GTK_FUNDAMENTAL_TYPE(arg->type) != GTK_TYPE_POINTER
        && GTK_FUNDAMENTAL_TYPE(arg->type) != type)
	ml_raise_gtk ("GtkArgv.Arg.set : argument type mismatch");
    switch (type) {
    case GTK_TYPE_CHAR:   *GTK_RETLOC_CHAR(*arg) = Int_val(data); break;
    case GTK_TYPE_BOOL:   *GTK_RETLOC_BOOL(*arg) = Int_val(data); break;
    case GTK_TYPE_INT:
    case GTK_TYPE_ENUM:   *GTK_RETLOC_INT(*arg) = Int_val(data); break;
    case GTK_TYPE_UINT:
    case GTK_TYPE_FLAGS:  *GTK_RETLOC_UINT(*arg) = Int32_val(data); break;
    case GTK_TYPE_LONG:
    case GTK_TYPE_ULONG:  *GTK_RETLOC_LONG(*arg) = Nativeint_val(data); break;
    case GTK_TYPE_FLOAT:  *GTK_RETLOC_FLOAT(*arg) = Float_val(data); break;
    case GTK_TYPE_DOUBLE: *GTK_RETLOC_DOUBLE(*arg) = Double_val(data); break;
    case GTK_TYPE_STRING:
         *GTK_RETLOC_STRING(*arg) = Option_val(data, String_val, NULL);
         break;
    case GTK_TYPE_OBJECT:
    case GTK_TYPE_BOXED:
    case GTK_TYPE_POINTER:
         *GTK_RETLOC_POINTER(*arg) = Option_val(data, Pointer_val, NULL);
         break;
    }
    return Val_unit;
}

CAMLprim value ml_gtk_arg_get_nativeint(GtkArg *arg) {

     switch(GTK_FUNDAMENTAL_TYPE(arg->type)) {
     case GTK_TYPE_INT:
     case GTK_TYPE_UINT:
          return copy_nativeint (GTK_VALUE_INT(*arg));
     case GTK_TYPE_LONG:
     case GTK_TYPE_ULONG:
          return copy_nativeint (GTK_VALUE_LONG(*arg));
     case GTK_TYPE_ENUM:
          return copy_nativeint (GTK_VALUE_ENUM(*arg));
     case GTK_TYPE_FLAGS:
          return copy_nativeint (GTK_VALUE_FLAGS(*arg));
     default:
          ml_raise_gtk ("argument type mismatch");
     }
     return Val_unit;
}

CAMLprim value ml_gtk_arg_get_pointer (GtkArg *arg)
{
    gpointer p = NULL;
    switch (GTK_FUNDAMENTAL_TYPE(arg->type)) {
    case GTK_TYPE_STRING:
    case GTK_TYPE_BOXED:
    case GTK_TYPE_POINTER:
    case G_TYPE_OBJECT:
        p = GTK_VALUE_POINTER(*arg); break;
    default:
	ml_raise_gtk ("GtkArgv.get_pointer : argument type mismatch");
    }
    return Val_pointer(p);
}
*/

/* gtksignal.h */

/*
CAMLprim value ml_gtk_signal_connect (value object, value name,
                                      value clos, value after)
{
    value *clos_p = ml_global_root_new (clos);
    return Val_int (gtk_signal_connect_full
		    (GtkObject_val(object), String_val(name), NULL,
		     ml_gtk_callback_marshal, clos_p,
		     ml_global_root_destroy, FALSE, Bool_val(after)));
}

ML_2 (gtk_signal_disconnect, GtkObject_val, Int_val, Unit)
ML_2 (gtk_signal_emit_stop_by_name, GtkObject_val, String_val, Unit)
ML_2 (gtk_signal_handler_block, GtkObject_val, Int_val, Unit)
ML_2 (gtk_signal_handler_unblock, GtkObject_val, Int_val, Unit)
ML_2_name (ml_gtk_signal_emit_none, gtk_signal_emit_by_name,
           GtkObject_val, String_val, Unit)
ML_3_name (ml_gtk_signal_emit_int, gtk_signal_emit_by_name,
           GtkObject_val, String_val, Int_val, Unit)
ML_4_name (ml_gtk_signal_emit_scroll, gtk_signal_emit_by_name,
           GtkObject_val, String_val, Scroll_type_val, Double_val, Unit)
*/

/* gtkmain.h (again) */

ML_1 (gtk_rc_add_default_file, String_val, Unit)