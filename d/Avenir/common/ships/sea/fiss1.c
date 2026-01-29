inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("Inside the fissure");
    set_long("The ship has sailed through the jagged opening of the " +
             "fissure.  Here the water runs swiftly and the walls rise "+
             "steeply to your right and left.  Ahead it looks like the "+
             "you will sail into a cave.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_item(({"wall","walls "}),
             "The walls if the fissure rent into the mountainside are " +
             "steep and unclimbable.\n");
    add_item("cave",
             "It looks like a wide, dark mouth from here.\n");

}  
