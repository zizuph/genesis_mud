inherit "/d/Earthsea/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_earthsea_room()
{
    set_short("On the sea");
    set_long("The dark blue sea surrounds the ship. You see "+
      "the blue dreamlike shore of Oranea quite close now.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
