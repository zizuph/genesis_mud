#include "/d/Ansalon/common/defs.h"

inherit "/std/room";

create_room()
{
    set_short("In the Blood Sea of Istar");
    set_long("The ship is sailing through the Blood Sea of Istar. To the " +
        "south you can make out a forested coastline.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
