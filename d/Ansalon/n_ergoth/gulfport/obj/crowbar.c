
/*
 * crowbar.c
 * A crowbar, to the old sailor's hidden whiskey stash
 * Town of Gulfport, Northern Ergoth
 * Tibbit, 30 April 1998
 *
 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("crowbar");
    set_adj("sturdy");
    add_adj("iron");

    set_short("sturdy iron crowbar");
    set_pshort("sturdy iron crowbars");
    set_long("This sturdy crowbar is constructed "+
        "of iron, and is black in color.  "+
        "One might use it to pry open chests or similar "+
        "containers.\n");

    add_prop(OBJ_I_WEIGHT,900);
    add_prop(OBJ_I_VOLUME, 70);
    add_prop(OBJ_I_VALUE, 178);

}

