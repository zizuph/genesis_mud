inherit "/d/Earthsea/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_earthsea_room()
{
    set_short("On the sea");
    set_long("The ship is surrounded by dark blue sea.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
