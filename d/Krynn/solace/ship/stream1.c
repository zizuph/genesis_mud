inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("On the Solace stream");
    set_long("You are floating along in the Solace Stream. " +
        "The banks are lined with forest. To the north is " +
        "Crystalmir Lake, while the stream continues " +
        "southwards.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
