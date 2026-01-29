/*
 * hall1.c
 *
 * Skippern 20(c)02
 *
 * A large hall inside a noble house.
 *
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <stdproperties.h>

void
create_inside()
{
    set_short("a large hall");
    set_long("This is inside a large hall.\n");

    add_exit(DOL_HILLS + "i-12/garden1", "east", 0, 1);
    add_exit(DOL_HILLS + "i-12/hall2", "south", 0, 1);
    add_exit(DOL_HILLS + "i-12/uphall1", "up", 0, 1);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
}


