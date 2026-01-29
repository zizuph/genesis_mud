#include "defs.h"

inherit MONASTERY_BASE;

#include <stdproperties.h>

nomask void
create_monastery_room()
{
    set_short("Hallway");
    set_long("   A short hallway that leads outside to a walkway " +
       "and east into a large room.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("m2_33", "east");
    add_exit("m2_13", "west");
    add_door_exit(0, MONASTERY_DIR + "m2_22", "south");
}
