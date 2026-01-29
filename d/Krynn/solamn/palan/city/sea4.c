inherit "/std/room";
#include <stdproperties.h>
#include "../local.h"

create_room()
{
    set_short("On the ocean");
    set_long("You are out on the ocean. A small island is barely visible to your north. " +
	     "A few seagulls fly overhead.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
