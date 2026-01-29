/*
 * anduin/cosg.c
 * On the Anduin river.
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
#include <stdproperties.h>

void
create_room()
{
    set_short("Somewhere on the River Anduin, near Osgiliath");
    set_long("You are in the middle of the river that is running southwards " +
        "to its mouth at the Bay of Belfalas. To the north, a mighty pillar " +
        "rises out of the water. It was probably once one of the piers " +
        "of the stone bridge connecting the western and eastern halves of " +
        "Osgiliath.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
