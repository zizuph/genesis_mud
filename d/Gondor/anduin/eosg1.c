/*
 * anduin/eosg1.c
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
#include <stdproperties.h>

void
create_room()
{
    set_short("Somewhere on the Anduin, near Eastern Osgiliath");
    set_long("You are somewhere on the river Anduin that is running south " +
        "towards its mouth in the Bay of Belfalas. The eastern shore " +
        "seems to be closer than the other one. All that you can make " +
        "out there are ruins like dark shadows.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
