/*
 * /d/Gondor/mordor/obj/square.c
 *
 * This is a square, used by a carpenter to draw a straight angle. There is no
 * special use for it yet, maybe I will add that later. It certainly is a
 * nice object that might be used in a quest. How about adding a pencil to
 * the environment to draw a nice angle?
 *
 * /Mercade, 26 October 1993
 *
 * Revision history:
 */

inherit "/std/object";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("square");
    add_name("tool");
    add_name("_square_at_cirith_ungol_");

    set_adj("carpenter");
    set_adj("straight");

    set_short("square");
    set_pshort("squares");

    set_long(BSN("It is a carpenter tool, used by the working orcs. It is " +
        "used to draw straight angles, mostly on wood to make chairs, " +
        "tables or prison doors."));

    add_prop(OBJ_I_VOLUME,  300);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE,   170);
}

/*
 * Recovery stuff
 */

string
query_recover()
{
    return MASTER;
}

void
init_recover(string arg)
{
    return;
}
