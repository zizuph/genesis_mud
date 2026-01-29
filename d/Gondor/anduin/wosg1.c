/*
 * anduin/wosg1.c
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
#include <stdproperties.h>

void
create_room()
{
    set_short("On the River Anduin close to Western Osgiliath");
    set_long("The river Anduin is running southwards. You are close to its " +
        "western shore. Some ancient ruins can be seen there on the river " +
        "bank.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
