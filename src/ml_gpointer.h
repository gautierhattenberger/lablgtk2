/* $Id: ml_gpointer.h,v 1.4 2005/10/17 11:52:03 garrigue Exp $ */

#define RegData_val(val) (Field(val,0))
#define RegPath_val(val) (Field(val,1))
#define RegOffset_val(val) (Long_val(Field(val,2)))
#define RegLength_val(val) (Long_val(Field(val,3)))

CAMLexport unsigned char* ml_gpointer_base (value region);
