#include "/d/Ansalon/common/defs.h"

inherit "/std/room";

create_room()
{
    set_short("In the Ergothian Sea");
    set_long("The ship is sailing in the Ergothian Sea, east of Northern " +
        "Ergoth.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
