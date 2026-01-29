inherit "/d/Earthsea/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_earthsea_room()
{
    set_short("On the sea");
    set_long("You are surrounded by deep blue sea. No trace of land "+
      "can be spoted.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

