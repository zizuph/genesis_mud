inherit "/std/room";
#include <stdproperties.h>
#include "../local.h"

create_room()
{
    set_short("Outside the bay of Cove");
    set_long("You can see land to the south, and a small bay opening up.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
