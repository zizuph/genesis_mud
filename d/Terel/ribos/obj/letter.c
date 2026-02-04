/*  A letter */

inherit "/std/object";
#include <stdproperties.h>

create_object()
{
   set_name("letter");
   set_adj("unmailed");
   set_long("Dear Bathai:\n" +
	    "Things are desperate here " +
	    "in Ribos.  An ancient evil is trying to escape from the "   +
	    "caves nearby.  Although the King has assured us that the " +
	    "knights will protect us, no one thinks they are strong "  +
	    "enough.  We will have left for Calathin by the time you " +
	    "get this, as will have almost everyone.  I just hope we " +
	    "get out before that 'Thing' does.  We'll see you in a few " +
	    "days.\n\n" +
	    "                                      Gombus\n");
   add_prop(OBJ_I_VALUE,  1);
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
}

