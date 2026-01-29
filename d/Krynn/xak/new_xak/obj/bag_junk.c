/*
 * The junk in Bupu's bag.
 * By Rastlin
 */
inherit "/std/object";

#include "../local.h"
#include <stdproperties.h>

public void
create_object()
{
    set_name("junk");
    set_short("lot of junk");

    set_long("It is a mix of rocks, mud, corpses of various dead " +
	     "animals and teeth. Stuff you wouldn't like to touch.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2000);

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GET, "You don't want to touch any of that filth.\n");
}
