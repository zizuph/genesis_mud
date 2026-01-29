/*
 *  /d/Gondor/guilds/rangers/ithilien/passage2.c
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
    set_short("a dark stairway landing");
    set_long("You are standing by the foot of a long stairway leading "
        + "up into darkness. The dark and narrow passage now continues "
        + "west, where you think you hear the faint sound of rushing "
        + "water.\n");
    add_item("passage","The passage is dark and narrow, with walls rough "
        + "and uneven. It runs west into darkness, and up a great many "
        + "steps also leading to darkness.\n");
    add_item(({"steps", "stairway"}), "The stairway consists of a great "
        + "many steps leading up into darkness. The steps are neatly "
        + "carved out of the rock, and are seemingly timeless.\n");
    add_item("water", "You see only a little water dripping from the "
        + "roof, but you hear a faint sound of rushing water in the "
        + "distance, and can taste it in the air.\n");
    add_item(({"roof", "walls", "floor"}), "The passage has been cut "
        + "through the very rock of this hill. The walls, roof and "
        + "floor are rough and uneven, and water drips from the "
        + "ceiling, gathering in pools.\n");
    add_exit(RANGERS_ITH_DIR + "passage1", "west", &check_ranger());
    add_exit(RANGERS_ITH_DIR + "passage3", "up", &check_ranger());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_SCRY, 1);

    reset_room();
}
