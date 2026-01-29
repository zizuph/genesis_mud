/*
 *  /d/Gondor/guilds/rangers/hq/track_task28.c
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
    set_short("A dead end");
    set_long("The trees close about you in all directions but to the "
        + "south. Due to the thick bushes growing beneath the trees, it seems "
        + "impossible to travel in any direction beyond that from which "
        + "you came.\n");

    track_add_items();
    
    add_item(({"bush", "bushes"}), "Bushes grow in thick clusters beneath "
        + "the trees. They block your passage in all directions but to "
        + "the south.\n");

    add_exit(TRACKTASK_DIR  + "track_task27",   "south", &allowed(), 1);

    reset_room();
}
