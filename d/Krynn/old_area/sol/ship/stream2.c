inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("On the Solace stream");
    set_long("You are in the southern reaches of the " +
        "Solace Stream. North, the stream continues, while " +
        "it flows into the Whiterage River to the south.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
