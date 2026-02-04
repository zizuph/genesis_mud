/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * fire_amulet.c
 *
 * Fire amulet
 *
 * modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
   set_name("amulet");
   set_adj("red");
   set_short("red amulet");
   set_long(
   "This is the Fire Amulet.  You can tell because of the painted " +
   "flames on the back.  It could only be the same Fire Amulet that " +
   "set the entire village of Camaris ablaze, killing hundreds.  It " +
   "feels rather cold now.  Probably couldn't melt ice now.\n");

   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 20);
   add_prop(OBJ_I_VALUE, 10);
}
