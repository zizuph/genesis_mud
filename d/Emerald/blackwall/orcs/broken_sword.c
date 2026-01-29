/* Fluff to fill the orc holy area. It can be found by searching the floor
   in cave15.c

   Code (c) 2000 to Damian Horton (BKA Casimir)
*/

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

inherit "/std/object";

create_object()
{
    set_name("hilt");
    add_name("sword");
    set_adj("sword");
    add_adj("broken");
    set_short("broken sword");
    set_long("A broken sword. This is only the hilt, with a few inches of "+
	     "corroded steel making up what is left of the blade. Though "+
	     "scoured by time, the hilt shows clear evidence of having "+
	     "once been ornately fashioned in a manner consistent with "+
	     "elvish design.\n");

    add_prop(OBJ_I_WEIGHT, 1950);
    add_prop(OBJ_I_VOLUME, 1250);
    add_prop(OBJ_I_VALUE, random(30)); 
}









