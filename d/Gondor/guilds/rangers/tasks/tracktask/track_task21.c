/*
 *  /d/Gondor/guilds/rangers/hq/track_task21.c
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
    set_long("The ground here slopes ever so slightly to the west "
        + "suggesting that somewhere in the distance lies a stream "
        + "or river. The path you have been following runs clearly "
        + "from east to west, following the grade of the land.\n");

    track_add_items();

    add_exit(TRACKTASK_DIR  + "track_task20",   "east", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task22",   "west", &allowed(), 1);

    reset_room();
}
