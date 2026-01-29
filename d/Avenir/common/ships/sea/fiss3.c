inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("Within the Rift of Sybarus");
    set_long("The opening of the fissure is still rather far away.  You " +
             "can see that some terrible force of nature was at work in "+
             "the formation of the Rift of Sybarus, for the mountain "+
             "is nearly cleaved in half, its walls jagged wounds.  The "+
             "ship is creeping slowly "+
             "forward against the force of the tide, even with the help "+
             "of a strong breeze from behind.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_item(({"wall","walls "}),
             "The walls of the fissure rent into the mountainside are " +
             "steep and unclimbable.\n");
    add_item("cave",
             "It looks like a wide, dark mouth from here.\n"); 

}  
