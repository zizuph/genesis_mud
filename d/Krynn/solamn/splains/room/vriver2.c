inherit "/std/room";
#include <stdproperties.h>
#include "../local.h"

create_room()
{
    set_short("On the mighty Vingaard River");
    set_long("You are still on the river somewhere between the ocean and " +
	     "Vingaard Keep. To your west you can see plains stretching " +
	     "out as far as your eye reaches, and to your east there " +
	     "is a forest visible, and mountains all the way back " +
	     "in the mists. The river itself winds into a northeasterly " +
	     "direction through the landscape.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);


}
