/*
 *  /d/Gondor/guilds/rangers/hq/ravine.c
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
        + "from west to east. You can follow the stream in both directions. You "
        + "might also be able to find purchase to move back up to the top of "
        + "the ravine.\n");
        
    track_add_items();
    
    add_item(({"stream", "slender stream"}), "The stream is very small, only a "
        + "trickle really. It flows in from the west and out to the east.\n");
    add_item(({"ravine", "depression"}), "The ravine is rather shallow, carved into "
        + "the floor of the forest over millenia by the little stream.\n");

    add_exit(TRACKTASK_DIR  + "ravine_west",   "west", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "ravine_east",   "east", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task19",   "up", &allowed(), 1, 1);

    reset_room();
}
