/* -*- Mode: C -*-
 *
 * thread.c
 *
 * A thin thread to be for sale in Dol Amroth.
 *
 * By Skippern 20(c)01
 */
inherit "/std/rope";

#include <stdproperties.h>

create_rope()
{
    set_name("thread");
    set_adj("thin");

    set_long("This thin thread looks fragile.\n");
	
	add_prop(OBJ_I_VALUE, 37);
}
