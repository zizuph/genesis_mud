#include "/d/Ansalon/common/defs.h"

inherit "/std/room";

create_room()
{
    set_short("Outside Port Balifor");
    set_long("The ship is in the Bay of Balifor, just outside Port " +
        "Balifor.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
