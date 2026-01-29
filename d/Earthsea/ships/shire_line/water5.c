inherit "/d/Earthsea/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_earthsea_room()
{
    set_short("On the sea");
    set_long("The dark blue sea surrounds the ship. You are prety "+
      "close to the shore , you can see Shire harbour from here.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
