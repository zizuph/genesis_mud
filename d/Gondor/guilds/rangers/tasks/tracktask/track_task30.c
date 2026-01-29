/*
 *  /d/Gondor/guilds/rangers/hq/track_task30.c
 *
 *  A room for the rabbit tracking apprentice task
 *
 *  Coded by Alto, 07 December 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../../rangers.h"

inherit TRACKTASK_DIR + "tracktask_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_gondor()
{
    set_short("A dead end");
    set_long("The trees here form a natural hall, the walls of which run "
        + "along the eastern and western margins of the path. The leaves "
        + "above form an almost perfect ceiling. The trees to the south "
        + "however, prevent your travel further in that direction.\n");
        
    add_item(({"hall", "long hall", "hall of trees"}), "The densely "
        + "growing trees to the east and west form a natural hall "
        + "of sorts, with the leaves overhead forming a roof.\n");

    track_add_items();

    add_exit(TRACKTASK_DIR  + "track_task5",   "north", &allowed(), 1);

    reset_room();
}
