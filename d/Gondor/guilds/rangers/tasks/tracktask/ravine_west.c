/*
 *  /d/Gondor/guilds/rangers/hq/ravine_west.c
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
    set_short("In a ravine");
    set_long("You are standing in a shallow ravine deep inside the Druedain forest. "
        + "A slender stream trickles through the middle of the depression, running "
        + "from west to east. Although the way east is clear, the western "
        + "part of the ravine is blocked up with logs.\n");
        
    track_add_items();
    
    add_item(({"stream", "slender stream"}), "The stream is very small, only a "
        + "trickle really. It flows in from the west and out to the south.\n");
    add_item(({"ravine", "depression"}), "The ravine is rather shallow, carved into "
        + "the floor of the forest over millenia by the little stream.\n");
    add_item(({"log", "logs"}), "Logs have been stacked across the small stream, "
        + "probably by a family of beavers. Some of the logs, however, have fallen "
        + "loose. Perhaps you could angle around them to the southwest.\n");

    add_exit(TRACKTASK_DIR  + "ravine",   "east", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "ravine_west_a",   "southwest", &allowed(), 1, 1);

    reset_room();
}
