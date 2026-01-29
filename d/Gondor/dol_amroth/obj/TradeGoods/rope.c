/* -*- Mode: C -*-
 *
 * rope.c
 *
 * A normal rope to be for sale in Dol Amroth.
 *
 * By Skippern 20(c)01
 */
inherit "/std/rope";

#include <stdproperties.h>

create_rope()
{
    set_name("rope");
    set_adj("brown");

    set_long("This brown rope is made out of hemp.\n");
	
	add_prop(OBJ_I_VALUE, 87);
}
