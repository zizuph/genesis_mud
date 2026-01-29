/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

void
create_object()
{
    seteuid(getuid());
    set_name("ewar");
    set_adj("tall");
    set_adj("chipped");
    set_short("tall chipped pitcher");
    set_long("This is "+short()+". It was made from white clay, and " +
        "looks elegant. It is tall with a narrow opening. There is a " +
        "flared lip which enables water, wine, or anything to be " +
        "poured from it. An elegant scroll handle is on the side of " +
        "the ewar to allow it to be held. Chips and small marks are " +
        "scattered across its surface.\n");

	add_prop(OBJ_I_WEIGHT, 2000);
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
