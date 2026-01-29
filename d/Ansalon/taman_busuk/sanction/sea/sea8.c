#include "/d/Ansalon/common/defs.h"

inherit "/std/room";

create_room()
{
    set_short("Out on the ocean");
    set_long("The ship is out on the ocean, probably somewhere north of " +
        "Nordmaar.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
