/*
 *  /d/Gondor/guilds/rangers/hq/track_task14.c
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
    set_short("On a rocky outcropping");
    set_long("You are standing on a large rock protruding from the "
        + "side of the hill. It is too high to jump from without hurting "
        + "yourself, and the only obvious place to go from here is "
        + "further along the outcropping to the west. Brambles seem "
        + "to prevent movement in all other directions.\n");

    track_add_items();
    
    add_item(({"rock", "rocky outcropping", "outcropping"}), "The "
        + "rock has been worn smooth by millenia of erosion. It is "
        + "flat on the top, making it possible to walk around on it.\n");
    add_item(({"hill", "small hill"}), "The hill is largely devoid of trees, "
        + "which makes it seem a bald spot rising out of the surrounding forest. "
        + "Although it bears few trees, brambles are in exceeding supply.\n");
    add_item(({"bramble", "brambles"}), "A careful look at the brambles reveals "
        + "a path smaller than that made by deer. Perhaps by rabbits? It runs "
        + "to the south.\n");
        
    add_exit(TRACKTASK_DIR + "outcropping",  "west", &allowed(), 1);
    add_exit(TRACKTASK_DIR + "track_task12", "south", &allowed(), 1, 1);

    reset_room();
}
