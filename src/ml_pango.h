/* $Id: ml_pango.h,v 1.3 2003/03/07 09:26:50 garrigue Exp $ */

#define PangoFontDescription_val(val) ((PangoFontDescription*)Pointer_val(val))
value Val_PangoFontDescription_new(PangoFontDescription* it);
#define Val_PangoFontDescription(desc) \
  (Val_PangoFontDescription_new(pango_font_description_copy(desc)))

value ml_PangoStyle_Val (value val);

#define Val_PangoLanguage Val_pointer
#define PangoLanguage_val Pointer_val

#define PangoContext_val(val) check_cast(PANGO_CONTEXT,val)
#define Val_PangoContext Val_GAnyObject
#define Val_PangoContext_new Val_GAnyObject_new

#define PangoFont_val(val) check_cast(PANGO_FONT, val)
#define Val_PangoFont Val_GAnyObject

#define PangoFontMetrics_val(val) ((PangoFontMetrics*)Pointer_val(val))
