/*
 *  /d/Gondor/guilds/rangers/hq/track_task20.c
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
        + "west. Due to the thick bushes growing beneath the trees, it seems "
        + "impossible to travel in any direction beyond that from which "
        + "you came.\n");

    track_add_items();
    
    add_item(({"bush", "bushes"}), "Bushes grow in thick clusters beneath "
        + "the trees. They block passage in most directions except for "
        + "the path leading to the east. On closer inspection, however, you "
        + "notice a small gap beneath some of the bushes to the southeast.\n");
    add_item(({"gap", "gap in the bushes"}), "Beneath some of the bushes "
        + "is a small gap, probably used by woodland creatures to scurry "
        + "through to the southeast. Although it looks rather tiny, you could "
        + "probably get through.\n");

    add_exit(TRACKTASK_DIR + "track_task18", "southeast", &allowed(), 1, 1);
    add_exit(TRACKTASK_DIR + "track_task21", "west", &allowed(), 1);

    reset_room();
}
