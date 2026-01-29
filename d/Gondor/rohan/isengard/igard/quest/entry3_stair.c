/*
 *  IGARD_QUEST + "entry3_stair.c"
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
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "deep_funcs.c";

public void        create_gondor();
public int         check_monster();

string
long_extratext()
{
    return "Looking up, you can see the sky through the opening "
    + "at the top of the stairs.\n";
}


public void
create_gondor()
{
    set_short("A narrow stairwell");
    set_long(stairwell_long_desc() + long_extratext());

    underground_add_items();
    stairwell_add_items();
    sky_add_items();

    add_item(({"room", "area", "surroundings", "place", "passage"}), 
        stairwell_long_desc() + long_extratext());
    add_item(({"opening"}), "You can see the sky through it.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_QUEST       + "furnace3_room",        "down");
    add_exit(IGARD_PLAIN_PATHS + "sw_dome2.c", "up", check_monster, 2, 0);

    reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();

}


public int
check_monster()
{
    if (TP->id("_igard_monster"))
    {
    return 1;
    }

    if (TP->query_attack() != 0)
    {
    TP->catch_tell("You start to run that direction, but quickly realise "
        + "that doing so would invite a quick death from below.\n");
    return 1;
    }

    write("With a sigh of relief, you venture back out into the open air "
        + "once again.\n");
    return 0;
}

