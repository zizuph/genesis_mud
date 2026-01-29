/*
 * File name  : boulder.c
 * Description: The large granite boulder, on which Shieldbearers train
 *              their shield slam, charging at it ;)
 *
 * Blizzard, 29.09.2003
 *
 */

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

public void
create_object()
{
    set_name("_neidar_boulder_rubble_");
    add_name("rubble");
    add_name(({ "remains", "stones", "debris" }));
    set_adj("large");
    add_adj(({ "heap", "of", "granite" }));
    set_short("large heap of rubble");
    set_long("It is a huge heap of rubble, that left after the granite " +
        "boulder collapsed.\n");
    

    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 400000);
    add_prop(OBJ_I_VOLUME, 350000);
}

