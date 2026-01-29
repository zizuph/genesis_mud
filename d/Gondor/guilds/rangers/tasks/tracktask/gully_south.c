/*
 *  /d/Gondor/guilds/rangers/hq/gully_south.c
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
        + "from north to south. Although the way north is clear, the northern "
        + "part of the gully is blocked up with logs.\n");
        
    track_add_items();
    
    add_item(({"stream", "slender stream"}), "The stream is very small, only a "
        + "trickle really. It flows in from the north and out to the south.\n");
    add_item(({"gully", "depression"}), "The gully is rather shallow, carved into "
        + "the floor of the forest over millenia by the little stream.\n");
    add_item(({"log", "logs"}), "Logs have been stacked across the small stream, "
        + "probably by a family of beavers. They render passage further to the "
        + "south impossible.\n");

    add_exit(TRACKTASK_DIR  + "gully",   "north", &allowed(), 1);

    reset_room();
}
