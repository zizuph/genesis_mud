/* -*- Mode: C -*-
 *
 * obj/leftover/g_horn
 *
 * Gargoyl horn as leftover.
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

void
create_object() 
{
    set_name("horn");
    set_adj("black");
    set_adj("long");
    set_short("long black horn");
    set_pshort("long black horns");
    set_long("This horn is long and black, and curved into a tight " +
	     "spiral. It looks like it have been torn of the head of " +
	     "a clay creature.\n"); 
    add_prop(OBJ_I_WEIGHT,2700);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,700);
}
