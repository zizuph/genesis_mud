/*
 *  /d/Gondor/guilds/rangers/hq/track_task2.c
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
    set_long("You are walking through the Druedain forest. The "
        + "trees draw close about you, and it is difficult to say "
        + "how deep within the forest you are. The path here looks "
        + "to have been made by wild animals. It runs to the east "
        + "and west.\n");

    track_add_items();

    add_exit(TRACKTASK_DIR  + "track_task1",   "east", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task3",   "west", &allowed(), 1);

    reset_room();
}
