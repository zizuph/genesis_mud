/*
 *  /d/Gondor/guilds/rangers/hq/track_task3.c
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
    set_short("Somewhere deep inside the Druedain forest");
    set_long("The trees seem closer than ever here. There is scarcely "
        + "room in some places to move between the trunks. Roots seem "
        + "to reach up from the ground to ensnare the unwary passerby. "
        + "The path here diverges in three directions.\n");

    track_add_items();

    add_exit(TRACKTASK_DIR  + "track_task2",   "east", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task4",   "north", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task5",   "south", &allowed(), 1);

    reset_room();
}
