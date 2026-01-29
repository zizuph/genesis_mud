inherit "/std/room";
#include <stdproperties.h>
#include "../local.h"

create_room()
{
    set_short("On the mighty Vingaard River");
    set_long("You are now shipping along the Vingaard River, a mighty stream flowing " +
	     "towards the ocean in the north. To your west is a small village where " +
	     "you can see many strange people running around. Far to the east there " +
	     "are mountains visible on the horizon, and there is a forest stretching " +
	     "almost all the way from the river to the mountains.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
