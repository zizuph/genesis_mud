inherit "/d/Krynn/std/cabin";

#include <stdproperties.h>
#include "local.h"

void
create_cabin()
{
    set_short("down in the hold");
    set_long("This is the hold of the troop ferry. Instead of cargo it " +
    "contains rough pallets where the ferried troop can rest on the trip.\n");

    add_item(({"pallets","rough pallets"}),"The pallets cover the floor " +
    "of the hold.\n");

    add_exit(SHIP_D + "deck","up",0);

    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship cuts through the waves.\n";
}

/* Needed for the map to know we are in a boat in a room somewhere else */
/*object
query_room_env()
{
      return environment(query_ship());
}
*/