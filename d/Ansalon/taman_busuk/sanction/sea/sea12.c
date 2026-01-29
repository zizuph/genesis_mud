#include "/d/Ansalon/common/defs.h"

inherit "/std/room";

create_room()
{
    set_short("In the Bay of Balifor");
    set_long("The ship is in the Bay of Balifor. To the south you see "+
        "Silvanesti, and Port Balifor is to the north.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
