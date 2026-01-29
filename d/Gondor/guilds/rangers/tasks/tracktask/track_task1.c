/*
 *  /d/Gondor/guilds/rangers/hq/track_task1.c
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
    set_short("A deserted path in the Druedain forest");
    set_long("You are standing somewhere in the Druedain forest, just "
        + "to the west of the central headquarters hideout. This part "
        + "of the forest seems very untravelled, and although the "
        + "forest creatures may pass now and then, few people have "
        + "ventured here. A path leads further into the forest to the "
        + "west and back to the hideout to the east.\n");

    track_add_items();

    add_item(({"hideout", "building"}), "Most of the building is hidden "
        + "among the trees. From here you can only see part of the west "
        + "wall.\n");
    add_item(({"central headquarters", "headquarters"}), "Psst. Don't "
        + "draw attention to it!\n");
    add_item(({"wall", "west wall"}), "The wall is constructed of wood "
        + "and shingle. Most of it is obscured by the trees.\n");
    add_item(({"wood", "shingle", "shingles"}), "The wall is made of wood "
        + "milled from the very forest about you. There are also wooden "
        + "shingles nailed to the wall, protecting it from the elements.\n");

    add_exit(TRACKTASK_DIR  + "track_task2",    "west", &allowed(), 1);
    add_exit(RANGERS_TASK + "task_room",   "east", 0, 1);

    reset_room();
}
