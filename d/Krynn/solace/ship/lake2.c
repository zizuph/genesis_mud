inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("On Crystalmir Lake");
    set_long("You are in the south basin of Crystalmir Lake. " +
        "Far to the northeast lies the village of Solace, while " +
        "the lake outflows into Solace Stream to the south.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
