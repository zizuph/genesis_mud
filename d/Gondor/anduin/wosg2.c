/*
 * anduin/wosg2.c
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room.c");
#include <stdproperties.h>

void
create_room()
{
    set_short("On the River Anduin close to Western Osgiliath");
    set_long("The Anduin River runs southwards towards the ocean. Some " +
        "distance to the west, ruins like dark shadows cover the river " +
        "bank.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
