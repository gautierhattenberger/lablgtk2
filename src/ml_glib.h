/* $Id: ml_glib.h,v 1.4 2000/11/16 08:15:16 garrigue Exp $ */

value copy_string_and_free (char *str); /* for g_strings only */
value Val_GList (GList *list, value (*func)(gpointer));
GList *GList_val (value list, gpointer (*func)(value));

/*
value Val_GSList (GSList *list, value (*func)(gpointer));
GSList *GSList_val (value list, gpointer (*func)(value));
*/
