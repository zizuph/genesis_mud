inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("Leaving the Rift of Sybarus");
    set_long("Leaving the cave formed by the forces of nature which "+
             "rent the mountain and created the Sybarus Rift, you can "+
             "see the natural sunlight far ahead.  The ship is creeping "+
             "slowly forward against the force of the tide.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_item(({"wall","walls "}),
             "The walls of the fissure rent into the mountainside are " +
             "steep and unclimbable.\n");
    add_item("cave",
             "It looks like a wide, dark mouth from here.\n"); 

}  
