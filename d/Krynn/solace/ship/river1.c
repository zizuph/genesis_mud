inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("On the WhiteRage River");
    set_long("You are on the Whiterage River, which empties " +
        "both Crystalmir Lake, and the rivers and streams of " +
        "Qualinesti. It empties out into the Newsea.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
