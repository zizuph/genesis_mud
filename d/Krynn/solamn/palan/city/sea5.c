inherit "/std/room";
#include <stdproperties.h>
#include "../local.h"

create_room()
{
    set_short("On the Ocean");
    set_long("You are out in the middle of the ocean, with only water around you.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
