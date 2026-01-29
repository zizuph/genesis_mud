inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("On Crystalmir Lake");
    set_long("You are on Crystalmir Lake. To the east you " +
        "can see the shore of the lake, as well as the pier " +
        "that is near the village of Solace.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
