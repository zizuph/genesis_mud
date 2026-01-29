/*
 *  IGARD_DEEP_ARMOURY + "entry_stair7.c"
 *
 *  Stairwell down to the armoury Isengard.
 *
 *  Last modified by Alto, 30 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "deep_funcs.c";

public void        create_gondor();

string
long_extratext()
{
    return "Looking up the stairwell, you see an almost imperceptible "
    + "increase in the light reflecting off the walls. Just to the north, "
    + "you see what looks like a massive armoury.\n";
}


public void
create_gondor()
{
    set_short("A narrow stairwell");
    set_long(stairwell_long_desc() + long_extratext());

    underground_add_items();
    stairwell_add_items();

    add_item(({"room", "area", "surroundings", "place", "passage"}), 
        stairwell_long_desc() + long_extratext());
    add_item(({"armoury", "massive armoury"}), "A huge room stuffed to "
        + "capacity with every kind of armoury imaginable lies just to "
        + "the north of here.\n");
    add_item(({"armour", "armours"}), "To see the armours in the armoury, "
        + "wouldn't it make sense to walk north and examine them more "
        + "closely?\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_ARMOURY   + "entry_stair6",        "up");
    add_exit(IGARD_DEEP_ARMOURY   + "armoury_shop",       "north");

    reset_room();
}
