/*
 *  /d/Gondor/guilds/rangers/hq/track_task15.c
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
    set_short("On top of a hill");
    set_long("You are standing on top of a small hill rising out of the "
        + "Druedain forest. From here you can see for miles in all directions. "
        + "Below you, to the west, a path descends back toward to trees. "
        + "You may also travel along the top of the hill to the east.\n");

    track_add_items();
    
    add_item(({"hill", "small hill"}), "The hill is largely devoid of trees, "
        + "which makes it seem a bald spot rising out of the surrounding forest. "
        + "Although it bears few trees, brambles are in exceeding supply.\n");
    add_item(({"bramble", "brambles"}), "The brambles grow in dense patches, "
        + "obscuring the ground.\n");
        
    add_exit(TRACKTASK_DIR + "track_task16",  "downhill", &allowed(), 1);
    add_exit(TRACKTASK_DIR + "track_task13", "east", &allowed(), 1);

    reset_room();
}
