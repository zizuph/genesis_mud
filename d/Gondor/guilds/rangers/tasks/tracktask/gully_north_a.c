/*
 *  /d/Gondor/guilds/rangers/hq/gully_north_a.c
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
    set_short("In a gully");
    set_long("You are standing in a shallow gully deep inside the Druedain forest. "
        + "A slender stream trickles through the middle of the depression, running "
        + "from north to south. It appears, however, that logs block your passage "
        + "both to the north and south.\n");
        
    track_add_items();
    
    add_item(({"stream", "slender stream"}), "The stream is very small, only a "
        + "trickle really. It flows in from the north and out to the south.\n");
    add_item(({"gully", "depression"}), "The gully is rather shallow, carved into "
        + "the floor of the forest over millenia by the little stream.\n");
    add_item(({"log", "logs"}), "Logs have been stacked across the small stream, "
        + "probably by a family of beavers. Some of the logs, however, have fallen "
        + "loose. Perhaps you could angle around them to the southwest.\n");

    add_exit(TRACKTASK_DIR  + "gully_north",   "southwest", &allowed(), 1, 1);

    reset_room();
}
