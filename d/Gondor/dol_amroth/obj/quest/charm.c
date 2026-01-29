/* -*- Mode: C -*-
 *
 * obj/quest/charm.c
 *
 * Skippern 20(c)02
 *
 * A lucky charm for somebody who beleaves in it.....
 */
inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_short("lucky charm");
    set_long("This is a lucky charm.\n");
    set_name("charm");
    add_name("TormirLuckyCharm");
    add_adj("lucky");
    
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_WEIGHT, 35);
    add_prop(OBJ_M_NO_SELL, "This is worthless for those who doesn't " +
	     "beleave in it");
}
