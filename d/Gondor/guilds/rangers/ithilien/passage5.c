/*
 *  /d/Gondor/guilds/rangers/ithilien/passage5.c
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
    set_short("A dark winding passage");
    set_long("The passage is so narrow here that you are brushing the stony "
        + "wall on either side. You hear the noise of rushing water to the "
        + "north. The passage enters utter darkness to the west, and "
        + "continues east.\n");
    add_item("wall","The stony walls are rough and narrow.\n");
    add_exit(RANGERS_ITH_DIR + "passage4", "west", &check_ranger());
    add_exit(RANGERS_ITH_DIR + "passage6", "east", &check_ranger());
    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_M_NO_SCRY, 1);
}
