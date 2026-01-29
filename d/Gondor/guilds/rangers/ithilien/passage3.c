/*
 *  /d/Gondor/guilds/rangers/ithilien/passage3.c
 *
 * Modification log:
 * 20-Jul-2001,Alto: more tidy up, change inheritance for new
 *                   rangers.
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "exit.c"

public void
create_gondor()
{
    set_short("A dark stairway");
    set_long("You are standing in a long and dark stairway passage, "
        + "with narrow walls, rough and uneven on both sides, and a "
        + "great many steps both above and below you. You see only "
        + "darkness in both directions.\n");
    add_item("passage", "The passage runs up and down here, both ways "
        + "leading to darkness. The rock walls are rough and uneven.\n");
    add_item(({"stairway","steps"}), "There are a great many steps in "
        + "this rock-carved stairway. A little water trickles down the "
        + "rough steps.\n");
    add_item("water", "A little water trickles down the rough steps.\n");
    add_item("walls", "The walls are roughly carved out of the rock.\n");
    add_exit(RANGERS_ITH_DIR + "passage4", "up", &check_ranger());
    add_exit(RANGERS_ITH_DIR + "passage2", "down", &check_ranger());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_SCRY, 1);
}
