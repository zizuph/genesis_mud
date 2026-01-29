/*
 *  /d/Gondor/guilds/rangers/hq/track_task5.c
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
    set_short("A narrow passage between the trees");
    set_long("The trees seem to part to either side on the east and "
        + "west of the path, forming a long hall through which you "
        + "may travel further to the south.\n");
        
    add_item(({"hall", "long hall", "hall of trees"}), "The densely "
        + "growing trees to the east and west form a natural hall "
        + "of sorts, with the leaves overhead forming a roof.\n");

    track_add_items();

    add_exit(TRACKTASK_DIR  + "track_task3",   "north", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task30",   "south", &allowed(), 1);

    reset_room();
}
