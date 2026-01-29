/* Fluff to fill the orc holy area. It can be found by searching the floor
   in cave2.c

   Code (c) 2000 to Damian Horton (BKA Casimir)
*/

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

inherit "/std/object";

create_object()
{
    set_name("thighbone");
    add_name("bone");
    set_adj("thigh");
    add_adj("broken");
    set_short("broken thighbone");
    set_long("The bigger portion of a broken thighbone from some humanoid "+
	     "creature of approximately human proportions. It is blackened "+
	     "and worn with age.\n");

    add_prop(OBJ_I_WEIGHT, 1300);
    add_prop(OBJ_I_VOLUME, 880);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_BUY, "That's disgusting! Why would I want that?!");
}









